
helloworld:     file format elf64-x86-64


Disassembly of section .init:

0000000000400590 <_init>:
  400590:	48 83 ec 08          	sub    $0x8,%rsp
  400594:	48 8b 05 5d 0a 20 00 	mov    0x200a5d(%rip),%rax        # 600ff8 <_DYNAMIC+0x1e0>
  40059b:	48 85 c0             	test   %rax,%rax
  40059e:	74 05                	je     4005a5 <_init+0x15>
  4005a0:	e8 1b 00 00 00       	callq  4005c0 <__gmon_start__@plt>
  4005a5:	48 83 c4 08          	add    $0x8,%rsp
  4005a9:	c3                   	retq   

Disassembly of section .plt:

00000000004005b0 <__gmon_start__@plt-0x10>:
  4005b0:	ff 35 52 0a 20 00    	pushq  0x200a52(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  4005b6:	ff 25 54 0a 20 00    	jmpq   *0x200a54(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  4005bc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004005c0 <__gmon_start__@plt>:
  4005c0:	ff 25 52 0a 20 00    	jmpq   *0x200a52(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  4005c6:	68 00 00 00 00       	pushq  $0x0
  4005cb:	e9 e0 ff ff ff       	jmpq   4005b0 <_init+0x20>

00000000004005d0 <_ZNSt8ios_base4InitC1Ev@plt>:
  4005d0:	ff 25 4a 0a 20 00    	jmpq   *0x200a4a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  4005d6:	68 01 00 00 00       	pushq  $0x1
  4005db:	e9 d0 ff ff ff       	jmpq   4005b0 <_init+0x20>

00000000004005e0 <__libc_start_main@plt>:
  4005e0:	ff 25 42 0a 20 00    	jmpq   *0x200a42(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  4005e6:	68 02 00 00 00       	pushq  $0x2
  4005eb:	e9 c0 ff ff ff       	jmpq   4005b0 <_init+0x20>

00000000004005f0 <__cxa_atexit@plt>:
  4005f0:	ff 25 3a 0a 20 00    	jmpq   *0x200a3a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  4005f6:	68 03 00 00 00       	pushq  $0x3
  4005fb:	e9 b0 ff ff ff       	jmpq   4005b0 <_init+0x20>

0000000000400600 <_ZNSt8ios_base4InitD1Ev@plt>:
  400600:	ff 25 32 0a 20 00    	jmpq   *0x200a32(%rip)        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  400606:	68 04 00 00 00       	pushq  $0x4
  40060b:	e9 a0 ff ff ff       	jmpq   4005b0 <_init+0x20>

0000000000400610 <write@plt>:
  400610:	ff 25 2a 0a 20 00    	jmpq   *0x200a2a(%rip)        # 601040 <_GLOBAL_OFFSET_TABLE_+0x40>
  400616:	68 05 00 00 00       	pushq  $0x5
  40061b:	e9 90 ff ff ff       	jmpq   4005b0 <_init+0x20>

Disassembly of section .text:

0000000000400620 <_start>:
  400620:	31 ed                	xor    %ebp,%ebp
  400622:	49 89 d1             	mov    %rdx,%r9
  400625:	5e                   	pop    %rsi
  400626:	48 89 e2             	mov    %rsp,%rdx
  400629:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40062d:	50                   	push   %rax
  40062e:	54                   	push   %rsp
  40062f:	49 c7 c0 40 08 40 00 	mov    $0x400840,%r8
  400636:	48 c7 c1 d0 07 40 00 	mov    $0x4007d0,%rcx
  40063d:	48 c7 c7 0d 07 40 00 	mov    $0x40070d,%rdi
  400644:	e8 97 ff ff ff       	callq  4005e0 <__libc_start_main@plt>
  400649:	f4                   	hlt    
  40064a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400650 <deregister_tm_clones>:
  400650:	b8 5f 10 60 00       	mov    $0x60105f,%eax
  400655:	55                   	push   %rbp
  400656:	48 2d 58 10 60 00    	sub    $0x601058,%rax
  40065c:	48 83 f8 0e          	cmp    $0xe,%rax
  400660:	48 89 e5             	mov    %rsp,%rbp
  400663:	77 02                	ja     400667 <deregister_tm_clones+0x17>
  400665:	5d                   	pop    %rbp
  400666:	c3                   	retq   
  400667:	b8 00 00 00 00       	mov    $0x0,%eax
  40066c:	48 85 c0             	test   %rax,%rax
  40066f:	74 f4                	je     400665 <deregister_tm_clones+0x15>
  400671:	5d                   	pop    %rbp
  400672:	bf 58 10 60 00       	mov    $0x601058,%edi
  400677:	ff e0                	jmpq   *%rax
  400679:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400680 <register_tm_clones>:
  400680:	b8 58 10 60 00       	mov    $0x601058,%eax
  400685:	55                   	push   %rbp
  400686:	48 2d 58 10 60 00    	sub    $0x601058,%rax
  40068c:	48 c1 f8 03          	sar    $0x3,%rax
  400690:	48 89 e5             	mov    %rsp,%rbp
  400693:	48 89 c2             	mov    %rax,%rdx
  400696:	48 c1 ea 3f          	shr    $0x3f,%rdx
  40069a:	48 01 d0             	add    %rdx,%rax
  40069d:	48 d1 f8             	sar    %rax
  4006a0:	75 02                	jne    4006a4 <register_tm_clones+0x24>
  4006a2:	5d                   	pop    %rbp
  4006a3:	c3                   	retq   
  4006a4:	ba 00 00 00 00       	mov    $0x0,%edx
  4006a9:	48 85 d2             	test   %rdx,%rdx
  4006ac:	74 f4                	je     4006a2 <register_tm_clones+0x22>
  4006ae:	5d                   	pop    %rbp
  4006af:	48 89 c6             	mov    %rax,%rsi
  4006b2:	bf 58 10 60 00       	mov    $0x601058,%edi
  4006b7:	ff e2                	jmpq   *%rdx
  4006b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004006c0 <__do_global_dtors_aux>:
  4006c0:	80 3d 91 09 20 00 00 	cmpb   $0x0,0x200991(%rip)        # 601058 <__TMC_END__>
  4006c7:	75 11                	jne    4006da <__do_global_dtors_aux+0x1a>
  4006c9:	55                   	push   %rbp
  4006ca:	48 89 e5             	mov    %rsp,%rbp
  4006cd:	e8 7e ff ff ff       	callq  400650 <deregister_tm_clones>
  4006d2:	5d                   	pop    %rbp
  4006d3:	c6 05 7e 09 20 00 01 	movb   $0x1,0x20097e(%rip)        # 601058 <__TMC_END__>
  4006da:	f3 c3                	repz retq 
  4006dc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004006e0 <frame_dummy>:
  4006e0:	48 83 3d 28 07 20 00 	cmpq   $0x0,0x200728(%rip)        # 600e10 <__JCR_END__>
  4006e7:	00 
  4006e8:	74 1e                	je     400708 <frame_dummy+0x28>
  4006ea:	b8 00 00 00 00       	mov    $0x0,%eax
  4006ef:	48 85 c0             	test   %rax,%rax
  4006f2:	74 14                	je     400708 <frame_dummy+0x28>
  4006f4:	55                   	push   %rbp
  4006f5:	bf 10 0e 60 00       	mov    $0x600e10,%edi
  4006fa:	48 89 e5             	mov    %rsp,%rbp
  4006fd:	ff d0                	callq  *%rax
  4006ff:	5d                   	pop    %rbp
  400700:	e9 7b ff ff ff       	jmpq   400680 <register_tm_clones>
  400705:	0f 1f 00             	nopl   (%rax)
  400708:	e9 73 ff ff ff       	jmpq   400680 <register_tm_clones>

000000000040070d <main>:
 * 
 *	nm helloworld to get symbol table
 *
 */

int main() {
  40070d:	55                   	push   %rbp
  40070e:	48 89 e5             	mov    %rsp,%rbp
	k*=k;
	cout << k << "\n";
	k++;
	cout << k << "\n";
	*/
	write(1, "Hello world\n", 13);
  400711:	ba 0d 00 00 00       	mov    $0xd,%edx
  400716:	be 55 08 40 00       	mov    $0x400855,%esi
  40071b:	bf 01 00 00 00       	mov    $0x1,%edi
  400720:	e8 eb fe ff ff       	callq  400610 <write@plt>
	write(1, "Hello\n", 7);
  400725:	ba 07 00 00 00       	mov    $0x7,%edx
  40072a:	be 62 08 40 00       	mov    $0x400862,%esi
  40072f:	bf 01 00 00 00       	mov    $0x1,%edi
  400734:	e8 d7 fe ff ff       	callq  400610 <write@plt>
	write(1, "world.\n", 8);
  400739:	ba 08 00 00 00       	mov    $0x8,%edx
  40073e:	be 69 08 40 00       	mov    $0x400869,%esi
  400743:	bf 01 00 00 00       	mov    $0x1,%edi
  400748:	e8 c3 fe ff ff       	callq  400610 <write@plt>
	write(1, "Hello worldz\n", 14);
  40074d:	ba 0e 00 00 00       	mov    $0xe,%edx
  400752:	be 71 08 40 00       	mov    $0x400871,%esi
  400757:	bf 01 00 00 00       	mov    $0x1,%edi
  40075c:	e8 af fe ff ff       	callq  400610 <write@plt>
	write(1, "Hi world\n", 10);
  400761:	ba 0a 00 00 00       	mov    $0xa,%edx
  400766:	be 7f 08 40 00       	mov    $0x40087f,%esi
  40076b:	bf 01 00 00 00       	mov    $0x1,%edi
  400770:	e8 9b fe ff ff       	callq  400610 <write@plt>
	
	char* string = malloc(5);
  400775:	b8 00 00 00 00       	mov    $0x0,%eax
	
  40077a:	5d                   	pop    %rbp
  40077b:	c3                   	retq   

000000000040077c <_Z41__static_initialization_and_destruction_0ii>:
  40077c:	55                   	push   %rbp
  40077d:	48 89 e5             	mov    %rsp,%rbp
  400780:	48 83 ec 10          	sub    $0x10,%rsp
  400784:	89 7d fc             	mov    %edi,-0x4(%rbp)
  400787:	89 75 f8             	mov    %esi,-0x8(%rbp)
  40078a:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
  40078e:	75 27                	jne    4007b7 <_Z41__static_initialization_and_destruction_0ii+0x3b>
  400790:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
  400797:	75 1e                	jne    4007b7 <_Z41__static_initialization_and_destruction_0ii+0x3b>
  extern wostream wclog;	/// Linked to standard error (buffered)
#endif
  //@}

  // For construction of filebuffers for cout, cin, cerr, clog et. al.
  static ios_base::Init __ioinit;
  400799:	bf 59 10 60 00       	mov    $0x601059,%edi
  40079e:	e8 2d fe ff ff       	callq  4005d0 <_ZNSt8ios_base4InitC1Ev@plt>
  4007a3:	ba 50 10 60 00       	mov    $0x601050,%edx
  4007a8:	be 59 10 60 00       	mov    $0x601059,%esi
  4007ad:	bf 00 06 40 00       	mov    $0x400600,%edi
  4007b2:	e8 39 fe ff ff       	callq  4005f0 <__cxa_atexit@plt>
  4007b7:	c9                   	leaveq 
  4007b8:	c3                   	retq   

00000000004007b9 <_GLOBAL__sub_I_main>:
  4007b9:	55                   	push   %rbp
  4007ba:	48 89 e5             	mov    %rsp,%rbp
  4007bd:	be ff ff 00 00       	mov    $0xffff,%esi
  4007c2:	bf 01 00 00 00       	mov    $0x1,%edi
  4007c7:	e8 b0 ff ff ff       	callq  40077c <_Z41__static_initialization_and_destruction_0ii>
  4007cc:	5d                   	pop    %rbp
  4007cd:	c3                   	retq   
  4007ce:	66 90                	xchg   %ax,%ax

00000000004007d0 <__libc_csu_init>:
  4007d0:	41 57                	push   %r15
  4007d2:	41 89 ff             	mov    %edi,%r15d
  4007d5:	41 56                	push   %r14
  4007d7:	49 89 f6             	mov    %rsi,%r14
  4007da:	41 55                	push   %r13
  4007dc:	49 89 d5             	mov    %rdx,%r13
  4007df:	41 54                	push   %r12
  4007e1:	4c 8d 25 10 06 20 00 	lea    0x200610(%rip),%r12        # 600df8 <__frame_dummy_init_array_entry>
  4007e8:	55                   	push   %rbp
  4007e9:	48 8d 2d 18 06 20 00 	lea    0x200618(%rip),%rbp        # 600e08 <__init_array_end>
  4007f0:	53                   	push   %rbx
  4007f1:	4c 29 e5             	sub    %r12,%rbp
  4007f4:	31 db                	xor    %ebx,%ebx
  4007f6:	48 c1 fd 03          	sar    $0x3,%rbp
  4007fa:	48 83 ec 08          	sub    $0x8,%rsp
  4007fe:	e8 8d fd ff ff       	callq  400590 <_init>
  400803:	48 85 ed             	test   %rbp,%rbp
  400806:	74 1e                	je     400826 <__libc_csu_init+0x56>
  400808:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40080f:	00 
  400810:	4c 89 ea             	mov    %r13,%rdx
  400813:	4c 89 f6             	mov    %r14,%rsi
  400816:	44 89 ff             	mov    %r15d,%edi
  400819:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40081d:	48 83 c3 01          	add    $0x1,%rbx
  400821:	48 39 eb             	cmp    %rbp,%rbx
  400824:	75 ea                	jne    400810 <__libc_csu_init+0x40>
  400826:	48 83 c4 08          	add    $0x8,%rsp
  40082a:	5b                   	pop    %rbx
  40082b:	5d                   	pop    %rbp
  40082c:	41 5c                	pop    %r12
  40082e:	41 5d                	pop    %r13
  400830:	41 5e                	pop    %r14
  400832:	41 5f                	pop    %r15
  400834:	c3                   	retq   
  400835:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40083c:	00 00 00 00 

0000000000400840 <__libc_csu_fini>:
  400840:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400844 <_fini>:
  400844:	48 83 ec 08          	sub    $0x8,%rsp
  400848:	48 83 c4 08          	add    $0x8,%rsp
  40084c:	c3                   	retq   
