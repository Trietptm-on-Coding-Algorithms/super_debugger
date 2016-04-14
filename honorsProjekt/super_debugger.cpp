//#include <bits/stdc++.h>
using namespace std;
#include <bfd.h>
#include <dis-asm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <assert.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <errno.h>
#include <readline/readline.h>
extern "C"{
#include "uthash.h"
}
#include <stdlib.h>
#include <unistd.h>
#include <bfd.h>
#include "utility"

//#include "parseValgrind.cpp"
#include "parseObjDump.cpp"
//#include <string>

typedef struct{
    char *sym;         /*symbol*/
    long addr;         /*symbol address*/
    long opc;          /*wrod at symbol*/
    UT_hash_handle hh; /*uthash handle*/
}SymbolTable, Symbol;

extern vector< x86 > x86_code;

/*
 *		Needs to compile with -g flag
 *
 *		Should have a modern version of valgrind/linux installed
 *
 *		Option to run with -f or --force to force continue
 *		./super_debugger -f ./yourProgram
 */ 
 
/*

			*** parseValgrind.cpp ***

struct errors {
  string errorMessage;
  vector< tuple<string, string, int> > description;
};


tuple<string, string, int> desLines;

// important
vector<errors> dividedErrors[9];
vector<errors> totalErrors;
vector<string> memory;


									***  Errors  *** 
0 - SIGSEGV
1 - Invalid read
2 - Invalid write
3 - Invalid free
4 - Mismatched free
5 - Source and destination		--- 	can handle right away
6 - Conditional jump
7 - Syscall										---		can handle right away	
8 - Argument fishy 						---		can handle right away 
 
*/  

/*

			*** parseObjDump.cpp ***

struct x86 {
  string line;
  int lineNum;
  vector< vector< string > > assembly;
};


vector< string > objectDump;
vector< string > mainFunct;							// only debugging main for now
vector< string > sourceFile;
string filename;

// important
vector< x86 > x86_code;

*/

struct user_regs_struct regs;

// struct to access stuff
struct user* user_space;

// Can have option to compile their file manually so they do not need to know compiler flags 

// helpers to get stuff
void* get_instr_ptr( pid_t pid ) {
	return ( void* )ptrace( PTRACE_PEEKUSER, pid, 8 * RIP,NULL );
}

void set_instr_ptr( pid_t pid, void* addr ) {
	ptrace( PTRACE_POKEUSER, pid, 8 * RIP, addr );
}

void* get_stack_ptr( pid_t pid ) {
	return ( void* )ptrace( PTRACE_PEEKUSER, pid, 8 * RSP, NULL );
}

void* get_ret_addr( pid_t pid, void* stack_pointer ) {
	return ( void* )ptrace( PTRACE_PEEKTEXT, pid, stack_pointer, NULL );
}

void* get_base_ptr(pid_t pid){
	return ( void* )ptrace( PTRACE_PEEKUSER, pid, 8 * RBP,NULL );
}

long get_data( pid_t pid, void* addr ) {
	return ptrace( PTRACE_PEEKDATA, pid, addr, NULL );
}

void set_data( pid_t pid, void* addr, void* data ) {
	ptrace( PTRACE_POKEDATA, pid, addr, data );
}

void step( pid_t pid ) {
	ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
}

// create breakpoint
pair< long, void* > set_brkpt( pid_t pid, void* addr ) {							
	// inject INT 3 = 0xCC --- this is an interrupt, sends signal to debugger
	long new_data = get_data( pid, addr );
	long former_data = new_data;
	new_data = ( new_data & ~0xFF ) | 0xCC;
	set_data( pid, addr, (void*)new_data );
	
	// need to store the former instruction pointer and data
	pair< long, void* > p;
	p = make_pair( former_data, addr );
	return p;
}

// set back instruction pointer
void handle_brkpt( pid_t pid, void* instr_ptr, void* data ) {
	set_data( pid, instr_ptr, data );
	set_instr_ptr( pid, instr_ptr );
}

/*debugger commands*/
typedef enum {CONTINUE, BREAK, KILL, NEXT, REGISTER, PRINT}cmd;

/*reads command from user*/
cmd next_cmd(char **argv)
{
    cmd cmd = REGISTER;

    char *cmdstr;
    if(!(cmdstr = readline("super_debugger -> "))) return cmd;

    if(!strcmp(cmdstr, "c") || !strcmp(cmdstr, "continue")){
        cmd = CONTINUE;
    }else if(!strcmp(cmdstr, "kill")){   
        cmd = KILL;
    }else if(!strcmp(cmdstr, "n") || !strcmp(cmdstr, "next")){
        cmd = NEXT;
    }else if(!strcmp(cmdstr, "reg") || !strcmp(cmdstr, "registers")){
        cmd = REGISTER;
    }else{
        const char *op = strtok(cmdstr, " ");
        const char *arg = strtok(NULL, " ");
        if( op && arg && (strcmp(op, "break") == 0 || !strcmp(op, "br")))
        {
            cmd = BREAK;
            *argv = strdup(arg);
        }else if( op && arg && (!strcmp(op, "print") || !strcmp(op, "p")))
        {
            cmd = PRINT;
            *argv = strdup(arg);
        }
    }
    free(cmdstr);
    return cmd;
}

pid_t create_child(char* argv[]){
	pid_t pid;
	switch(pid = fork())
    {
        case -1: /*error*/
        {
            perror("fork()");
            exit(-1);
        }   

        case 0:/*child process*/
        {
            ptrace(PTRACE_TRACEME, NULL, NULL);     /*allow child process to be traced*/
            execvp(argv[1], argv+1);                /*child will be stopped here*/
            perror("execvp()");
            exit(-1);
        }
        
        /*parent continues execution*/
    }

    return pid;
}

int main( int argc, char* argv[] ) {
	if ( argc < 2 ) {
		printf("\n\t\e[1mFormat is: ./super_debugger [-f / --force] ./your_program\e[0m\n\n");
		return 0;
	} 

	// execute and parse valgrind output	
	int k = 0;// = execValgrind( argc, argv ); 			
	
	if ( k ) 							
		return 0;		// return early if not forced or if something bad happened

	// execute and parse object dump of program
	k = execObjDump( argc, argv );
	
	if ( k ) 							
		return 0;		
	
	vector<pair<string, long>> symbols;
	// run our debugger
	void* mainpoint;
	int main_point_hit = 0;
	long main_dat;
	long main_addr;
	pid_t pid = create_child(argv);
	char *arg;
    int status;
    long addr = 0;
    long opcode[2];
    long old_rip;
    long opc;
    wait(&status);

	for(auto i = x86_code.begin(); i != x86_code.end(); ++i){
		if(i->line.find("main()") != string::npos){
				main_addr =  strtol(i->assembly[0][0].c_str(), NULL, 16)+3;
				printf("%lx\n", main_addr);
				main_dat = ptrace(PTRACE_PEEKTEXT, pid, main_addr, NULL);                    
                ptrace(PTRACE_POKETEXT, pid, main_addr, 0xcc); 
		}
		for(auto j = i->assembly.begin(); j != i->assembly.end(); ++j){
			auto temp = *j;
			long a = strtoll(temp[2].c_str(), NULL, 16);
			if(a == 0)
				continue;
			symbols.push_back(make_pair(i->line, a));
		}
	}


    while(1)
    {       
        if(WIFEXITED(status) || (WIFSIGNALED(status) && WTERMSIG(status) == SIGKILL))
        {
            printf("process %d terminated\n", pid);
            exit(0);
        }
        if(WIFSTOPPED(status))
        {
        	long rip =  ptrace(PTRACE_PEEKUSER, pid, 8 * RIP, NULL)-1;
        	printf("process %d stopped at 0x%lx\n", pid, rip);
        	if(rip == addr){
        		ptrace(PTRACE_POKETEXT, pid, addr, opc);
	            /*decrement eip*/ 
	            ptrace(PTRACE_POKEUSER, pid, 8 * RIP, rip);
                /*read instruction pointer*/
        	}
        	if(rip == main_addr){
        		
        		long rbp =  ptrace(PTRACE_PEEKUSER, pid, 8 * RBP, NULL);
        		printf("%lx\n", rbp);
                for(size_t i = 0; i != symbols.size(); ++i){
                	cout << symbols[i].second << " ";
                	symbols[i].second = rbp + symbols[i].second;
                	cout << symbols[i].first;
                	printf(" %lx\n", symbols[i].second);
                }

        		ptrace(PTRACE_POKETEXT, pid, main_addr, main_dat);
	            /*decrement eip*/ 
	            ptrace(PTRACE_POKEUSER, pid, 8 * RIP, rip);
        	}

        }
        switch(next_cmd(&arg))
        {
            case BREAK: /*set break point*/
            {
                addr = strtol(arg, NULL, 16);
                /*save instruction at eip*/
                /*insert break point*/
                opc = ptrace(PTRACE_PEEKTEXT, pid, addr, NULL);                    
                ptrace(PTRACE_POKETEXT, pid, addr, 0xcc);
                printf("breakpoint at Instruction %lu\n", addr);             
                free(arg);
                break;
            }

            case PRINT:
            {
            	for(size_t i = 0; i != symbols.size(); ++i){
            		printf("%lx %s\n", symbols[i].second, symbols[i].first.c_str());
                }
            	int found = 0;
            	for(auto i = symbols.begin(); i != symbols.end(); ++i){
            		if(strcmp(i->first.c_str(), arg) == 0){
            			found = 1;
            			printf("%s is %lx\n", i->first.c_str(), ptrace( PTRACE_PEEKTEXT, pid, i->second, NULL ));
            			break;
            		}
            	}
            	if(!found){
            		printf("Symbol not found in scope\n");
            	}
            	break;
            }

            case NEXT: /*next instruction*/
            {
                long rip =  ptrace(PTRACE_PEEKUSER, pid, 8 * RIP, NULL);

                /*read two words at eip*/
                opcode[0] = ptrace(PTRACE_PEEKDATA, pid, rip, NULL);
                opcode[1] = ptrace(PTRACE_PEEKDATA, pid, rip+sizeof(long), NULL);
                old_rip = rip;

                /*next instruction*/
                ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
                wait(&status);
                break;
            }

            case REGISTER:/*dump registers*/
            {
                struct user_regs_struct regs;
                ptrace(PTRACE_GETREGS, pid, NULL, &regs);
                printf("rax 0x%lx\n", regs.rax);
                printf("rbx 0x%lx\n", regs.rbx);
                printf("rcx 0x%lx\n", regs.rcx);
                printf("rdx 0x%lx\n", regs.rdx);
                printf("rsi 0x%lx\n", regs.rsi);
                printf("rdi 0x%lx\n", regs.rdi);
                printf("rbp 0x%lx\n", regs.rbp);
                printf("rsp 0x%lx\n", regs.rsp);
                printf("rip 0x%lx\n", regs.rip);
                break;
            }
            case CONTINUE:/*continue execution*/
	            /*decrement eip*/ 
                ptrace(PTRACE_CONT, pid, NULL, NULL);
                wait(&status);
                break;

            case KILL: /*kill process*/
                kill(pid, SIGKILL);
                wait(&status);
                break;

            default:/*error*/
                fprintf(stderr, "invalid or unknown command\n");
        }
    }

	return 0;
}
