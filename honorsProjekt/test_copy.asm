
./test:     file format elf64-x86-64


Disassembly of section .init:

0000000000400528 <_init>:
_init():
  400528:	48 83 ec 08          	sub    $0x8,%rsp
  40052c:	48 8b 05 c5 0a 20 00 	mov    0x200ac5(%rip),%rax        # 600ff8 <_DYNAMIC+0x1d0>
  400533:	48 85 c0             	test   %rax,%rax
  400536:	74 05                	je     40053d <_init+0x15>
  400538:	e8 83 00 00 00       	callq  4005c0 <__gmon_start__@plt>
  40053d:	48 83 c4 08          	add    $0x8,%rsp
  400541:	c3                   	retq   

Disassembly of section .plt:

0000000000400550 <free@plt-0x10>:
  400550:	ff 35 b2 0a 20 00    	pushq  0x200ab2(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400556:	ff 25 b4 0a 20 00    	jmpq   *0x200ab4(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40055c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400560 <free@plt>:
  400560:	ff 25 b2 0a 20 00    	jmpq   *0x200ab2(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400566:	68 00 00 00 00       	pushq  $0x0
  40056b:	e9 e0 ff ff ff       	jmpq   400550 <_init+0x28>

0000000000400570 <strcpy@plt>:
  400570:	ff 25 aa 0a 20 00    	jmpq   *0x200aaa(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400576:	68 01 00 00 00       	pushq  $0x1
  40057b:	e9 d0 ff ff ff       	jmpq   400550 <_init+0x28>

0000000000400580 <write@plt>:
  400580:	ff 25 a2 0a 20 00    	jmpq   *0x200aa2(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  400586:	68 02 00 00 00       	pushq  $0x2
  40058b:	e9 c0 ff ff ff       	jmpq   400550 <_init+0x28>

0000000000400590 <strlen@plt>:
  400590:	ff 25 9a 0a 20 00    	jmpq   *0x200a9a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  400596:	68 03 00 00 00       	pushq  $0x3
  40059b:	e9 b0 ff ff ff       	jmpq   400550 <_init+0x28>

00000000004005a0 <__libc_start_main@plt>:
  4005a0:	ff 25 92 0a 20 00    	jmpq   *0x200a92(%rip)        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  4005a6:	68 04 00 00 00       	pushq  $0x4
  4005ab:	e9 a0 ff ff ff       	jmpq   400550 <_init+0x28>

00000000004005b0 <calloc@plt>:
  4005b0:	ff 25 8a 0a 20 00    	jmpq   *0x200a8a(%rip)        # 601040 <_GLOBAL_OFFSET_TABLE_+0x40>
  4005b6:	68 05 00 00 00       	pushq  $0x5
  4005bb:	e9 90 ff ff ff       	jmpq   400550 <_init+0x28>

00000000004005c0 <__gmon_start__@plt>:
  4005c0:	ff 25 82 0a 20 00    	jmpq   *0x200a82(%rip)        # 601048 <_GLOBAL_OFFSET_TABLE_+0x48>
  4005c6:	68 06 00 00 00       	pushq  $0x6
  4005cb:	e9 80 ff ff ff       	jmpq   400550 <_init+0x28>

00000000004005d0 <malloc@plt>:
  4005d0:	ff 25 7a 0a 20 00    	jmpq   *0x200a7a(%rip)        # 601050 <_GLOBAL_OFFSET_TABLE_+0x50>
  4005d6:	68 07 00 00 00       	pushq  $0x7
  4005db:	e9 70 ff ff ff       	jmpq   400550 <_init+0x28>

Disassembly of section .text:

00000000004005e0 <_start>:
_start():
  4005e0:	31 ed                	xor    %ebp,%ebp
  4005e2:	49 89 d1             	mov    %rdx,%r9
  4005e5:	5e                   	pop    %rsi
  4005e6:	48 89 e2             	mov    %rsp,%rdx
  4005e9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4005ed:	50                   	push   %rax
  4005ee:	54                   	push   %rsp
  4005ef:	49 c7 c0 80 0a 40 00 	mov    $0x400a80,%r8
  4005f6:	48 c7 c1 10 0a 40 00 	mov    $0x400a10,%rcx
  4005fd:	48 c7 c7 0a 07 40 00 	mov    $0x40070a,%rdi
  400604:	e8 97 ff ff ff       	callq  4005a0 <__libc_start_main@plt>
  400609:	f4                   	hlt    
  40060a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400610 <deregister_tm_clones>:
deregister_tm_clones():
  400610:	b8 6f 10 60 00       	mov    $0x60106f,%eax
  400615:	55                   	push   %rbp
  400616:	48 2d 68 10 60 00    	sub    $0x601068,%rax
  40061c:	48 83 f8 0e          	cmp    $0xe,%rax
  400620:	48 89 e5             	mov    %rsp,%rbp
  400623:	77 02                	ja     400627 <deregister_tm_clones+0x17>
  400625:	5d                   	pop    %rbp
  400626:	c3                   	retq   
  400627:	b8 00 00 00 00       	mov    $0x0,%eax
  40062c:	48 85 c0             	test   %rax,%rax
  40062f:	74 f4                	je     400625 <deregister_tm_clones+0x15>
  400631:	5d                   	pop    %rbp
  400632:	bf 68 10 60 00       	mov    $0x601068,%edi
  400637:	ff e0                	jmpq   *%rax
  400639:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400640 <register_tm_clones>:
register_tm_clones():
  400640:	b8 68 10 60 00       	mov    $0x601068,%eax
  400645:	55                   	push   %rbp
  400646:	48 2d 68 10 60 00    	sub    $0x601068,%rax
  40064c:	48 c1 f8 03          	sar    $0x3,%rax
  400650:	48 89 e5             	mov    %rsp,%rbp
  400653:	48 89 c2             	mov    %rax,%rdx
  400656:	48 c1 ea 3f          	shr    $0x3f,%rdx
  40065a:	48 01 d0             	add    %rdx,%rax
  40065d:	48 d1 f8             	sar    %rax
  400660:	75 02                	jne    400664 <register_tm_clones+0x24>
  400662:	5d                   	pop    %rbp
  400663:	c3                   	retq   
  400664:	ba 00 00 00 00       	mov    $0x0,%edx
  400669:	48 85 d2             	test   %rdx,%rdx
  40066c:	74 f4                	je     400662 <register_tm_clones+0x22>
  40066e:	5d                   	pop    %rbp
  40066f:	48 89 c6             	mov    %rax,%rsi
  400672:	bf 68 10 60 00       	mov    $0x601068,%edi
  400677:	ff e2                	jmpq   *%rdx
  400679:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400680 <__do_global_dtors_aux>:
__do_global_dtors_aux():
  400680:	80 3d e1 09 20 00 00 	cmpb   $0x0,0x2009e1(%rip)        # 601068 <__TMC_END__>
  400687:	75 11                	jne    40069a <__do_global_dtors_aux+0x1a>
  400689:	55                   	push   %rbp
  40068a:	48 89 e5             	mov    %rsp,%rbp
  40068d:	e8 7e ff ff ff       	callq  400610 <deregister_tm_clones>
  400692:	5d                   	pop    %rbp
  400693:	c6 05 ce 09 20 00 01 	movb   $0x1,0x2009ce(%rip)        # 601068 <__TMC_END__>
  40069a:	f3 c3                	repz retq 
  40069c:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004006a0 <frame_dummy>:
frame_dummy():
  4006a0:	48 83 3d 78 07 20 00 	cmpq   $0x0,0x200778(%rip)        # 600e20 <__JCR_END__>
  4006a7:	00 
  4006a8:	74 1e                	je     4006c8 <frame_dummy+0x28>
  4006aa:	b8 00 00 00 00       	mov    $0x0,%eax
  4006af:	48 85 c0             	test   %rax,%rax
  4006b2:	74 14                	je     4006c8 <frame_dummy+0x28>
  4006b4:	55                   	push   %rbp
  4006b5:	bf 20 0e 60 00       	mov    $0x600e20,%edi
  4006ba:	48 89 e5             	mov    %rsp,%rbp
  4006bd:	ff d0                	callq  *%rax
  4006bf:	5d                   	pop    %rbp
  4006c0:	e9 7b ff ff ff       	jmpq   400640 <register_tm_clones>
  4006c5:	0f 1f 00             	nopl   (%rax)
  4006c8:	e9 73 ff ff ff       	jmpq   400640 <register_tm_clones>

00000000004006cd <strdup>:
strdup():
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:13
  4006cd:	55                   	push   %rbp
  4006ce:	48 89 e5             	mov    %rsp,%rbp
  4006d1:	48 83 ec 20          	sub    $0x20,%rsp
  4006d5:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:14
  4006d9:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  4006dd:	48 89 c7             	mov    %rax,%rdi
  4006e0:	e8 ab fe ff ff       	callq  400590 <strlen@plt>
  4006e5:	48 89 c7             	mov    %rax,%rdi
  4006e8:	e8 e3 fe ff ff       	callq  4005d0 <malloc@plt>
  4006ed:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:15
  4006f1:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  4006f5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4006f9:	48 89 d6             	mov    %rdx,%rsi
  4006fc:	48 89 c7             	mov    %rax,%rdi
  4006ff:	e8 6c fe ff ff       	callq  400570 <strcpy@plt>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:16
  400704:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:17
  400708:	c9                   	leaveq 
  400709:	c3                   	retq   

000000000040070a <main>:
main():
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:19
  40070a:	55                   	push   %rbp
  40070b:	48 89 e5             	mov    %rsp,%rbp
  40070e:	53                   	push   %rbx
  40070f:	48 83 ec 68          	sub    $0x68,%rsp
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:20
  400713:	48 c7 45 a8 98 0a 40 	movq   $0x400a98,-0x58(%rbp)
  40071a:	00 
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:21
  40071b:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  40071f:	48 89 c7             	mov    %rax,%rdi
  400722:	e8 a6 ff ff ff       	callq  4006cd <strdup>
  400727:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:22
  40072b:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  40072f:	48 89 c7             	mov    %rax,%rdi
  400732:	e8 59 fe ff ff       	callq  400590 <strlen@plt>
  400737:	48 8b 55 b0          	mov    -0x50(%rbp),%rdx
  40073b:	48 01 d0             	add    %rdx,%rax
  40073e:	c6 00 0a             	movb   $0xa,(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:25
  400741:	bf 15 00 00 00       	mov    $0x15,%edi
  400746:	e8 85 fe ff ff       	callq  4005d0 <malloc@plt>
  40074b:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:26
  40074f:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  400753:	48 bb 57 69 74 68 20 	movabs $0x20724f2068746957,%rbx
  40075a:	4f 72 20 
  40075d:	48 89 18             	mov    %rbx,(%rax)
  400760:	48 bb 57 69 74 68 6f 	movabs $0x2074756f68746957,%rbx
  400767:	75 74 20 
  40076a:	48 89 58 08          	mov    %rbx,0x8(%rax)
  40076e:	c7 40 10 59 6f 75 00 	movl   $0x756f59,0x10(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:27
  400775:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  400779:	48 89 c7             	mov    %rax,%rdi
  40077c:	e8 0f fe ff ff       	callq  400590 <strlen@plt>
  400781:	48 8b 55 b8          	mov    -0x48(%rbp),%rdx
  400785:	48 01 d0             	add    %rdx,%rax
  400788:	c6 00 0a             	movb   $0xa,(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:30
  40078b:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  40078f:	48 89 c7             	mov    %rax,%rdi
  400792:	e8 c9 fd ff ff       	callq  400560 <free@plt>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:31
  400797:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  40079b:	48 89 c7             	mov    %rax,%rdi
  40079e:	e8 bd fd ff ff       	callq  400560 <free@plt>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:33
  4007a3:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  4007a7:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:34
  4007ab:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  4007af:	c6 00 4f             	movb   $0x4f,(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:35
  4007b2:	48 83 45 b0 01       	addq   $0x1,-0x50(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:36
  4007b7:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  4007bb:	c6 00 6e             	movb   $0x6e,(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:37
  4007be:	48 83 45 b0 01       	addq   $0x1,-0x50(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:38
  4007c3:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  4007c7:	c6 00 65             	movb   $0x65,(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:39
  4007ca:	48 83 45 b0 01       	addq   $0x1,-0x50(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:40
  4007cf:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  4007d3:	c6 00 0a             	movb   $0xa,(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:41
  4007d6:	48 83 45 b0 01       	addq   $0x1,-0x50(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:42
  4007db:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  4007df:	c6 00 00             	movb   $0x0,(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:45
  4007e2:	bf 30 00 00 00       	mov    $0x30,%edi
  4007e7:	e8 e4 fd ff ff       	callq  4005d0 <malloc@plt>
  4007ec:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:46
  4007f0:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
  4007f7:	eb 2b                	jmp    400824 <main+0x11a>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:47 (discriminator 2)
  4007f9:	8b 45 90             	mov    -0x70(%rbp),%eax
  4007fc:	48 98                	cltq   
  4007fe:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400805:	00 
  400806:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  40080a:	48 8d 1c 02          	lea    (%rdx,%rax,1),%rbx
  40080e:	be 04 00 00 00       	mov    $0x4,%esi
  400813:	bf 06 00 00 00       	mov    $0x6,%edi
  400818:	e8 93 fd ff ff       	callq  4005b0 <calloc@plt>
  40081d:	48 89 03             	mov    %rax,(%rbx)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:46 (discriminator 2)
  400820:	83 45 90 01          	addl   $0x1,-0x70(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:46 (discriminator 1)
  400824:	83 7d 90 05          	cmpl   $0x5,-0x70(%rbp)
  400828:	7e cf                	jle    4007f9 <main+0xef>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:50
  40082a:	c7 45 94 01 00 00 00 	movl   $0x1,-0x6c(%rbp)
  400831:	e9 b2 00 00 00       	jmpq   4008e8 <main+0x1de>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:51
  400836:	8b 45 94             	mov    -0x6c(%rbp),%eax
  400839:	48 98                	cltq   
  40083b:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400842:	00 
  400843:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  400847:	48 01 d0             	add    %rdx,%rax
  40084a:	48 8b 00             	mov    (%rax),%rax
  40084d:	c7 00 01 00 00 00    	movl   $0x1,(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:53
  400853:	c7 45 98 01 00 00 00 	movl   $0x1,-0x68(%rbp)
  40085a:	eb 7e                	jmp    4008da <main+0x1d0>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:54 (discriminator 2)
  40085c:	8b 45 94             	mov    -0x6c(%rbp),%eax
  40085f:	48 98                	cltq   
  400861:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400868:	00 
  400869:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  40086d:	48 01 d0             	add    %rdx,%rax
  400870:	48 8b 00             	mov    (%rax),%rax
  400873:	8b 55 98             	mov    -0x68(%rbp),%edx
  400876:	48 63 d2             	movslq %edx,%rdx
  400879:	48 c1 e2 02          	shl    $0x2,%rdx
  40087d:	48 01 d0             	add    %rdx,%rax
  400880:	8b 55 94             	mov    -0x6c(%rbp),%edx
  400883:	48 63 d2             	movslq %edx,%rdx
  400886:	48 c1 e2 03          	shl    $0x3,%rdx
  40088a:	48 8d 4a f8          	lea    -0x8(%rdx),%rcx
  40088e:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  400892:	48 01 ca             	add    %rcx,%rdx
  400895:	48 8b 12             	mov    (%rdx),%rdx
  400898:	8b 4d 98             	mov    -0x68(%rbp),%ecx
  40089b:	48 63 c9             	movslq %ecx,%rcx
  40089e:	48 c1 e1 02          	shl    $0x2,%rcx
  4008a2:	48 83 e9 04          	sub    $0x4,%rcx
  4008a6:	48 01 ca             	add    %rcx,%rdx
  4008a9:	8b 0a                	mov    (%rdx),%ecx
  4008ab:	8b 55 94             	mov    -0x6c(%rbp),%edx
  4008ae:	48 63 d2             	movslq %edx,%rdx
  4008b1:	48 c1 e2 03          	shl    $0x3,%rdx
  4008b5:	48 8d 72 f8          	lea    -0x8(%rdx),%rsi
  4008b9:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  4008bd:	48 01 f2             	add    %rsi,%rdx
  4008c0:	48 8b 12             	mov    (%rdx),%rdx
  4008c3:	8b 75 98             	mov    -0x68(%rbp),%esi
  4008c6:	48 63 f6             	movslq %esi,%rsi
  4008c9:	48 c1 e6 02          	shl    $0x2,%rsi
  4008cd:	48 01 f2             	add    %rsi,%rdx
  4008d0:	8b 12                	mov    (%rdx),%edx
  4008d2:	01 ca                	add    %ecx,%edx
  4008d4:	89 10                	mov    %edx,(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:53 (discriminator 2)
  4008d6:	83 45 98 01          	addl   $0x1,-0x68(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:53 (discriminator 1)
  4008da:	83 7d 98 05          	cmpl   $0x5,-0x68(%rbp)
  4008de:	0f 8e 78 ff ff ff    	jle    40085c <main+0x152>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:50
  4008e4:	83 45 94 01          	addl   $0x1,-0x6c(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:50 (discriminator 1)
  4008e8:	83 7d 94 05          	cmpl   $0x5,-0x6c(%rbp)
  4008ec:	0f 8e 44 ff ff ff    	jle    400836 <main+0x12c>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:57
  4008f2:	c7 45 9c 00 00 00 00 	movl   $0x0,-0x64(%rbp)
  4008f9:	eb 36                	jmp    400931 <main+0x227>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:58
  4008fb:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
  400902:	eb 23                	jmp    400927 <main+0x21d>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:62 (discriminator 2)
  400904:	8b 45 9c             	mov    -0x64(%rbp),%eax
  400907:	48 98                	cltq   
  400909:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400910:	00 
  400911:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  400915:	48 01 d0             	add    %rdx,%rax
  400918:	48 8b 00             	mov    (%rax),%rax
  40091b:	48 89 c7             	mov    %rax,%rdi
  40091e:	e8 3d fc ff ff       	callq  400560 <free@plt>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:58 (discriminator 2)
  400923:	83 45 a0 01          	addl   $0x1,-0x60(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:58 (discriminator 1)
  400927:	83 7d a0 06          	cmpl   $0x6,-0x60(%rbp)
  40092b:	7e d7                	jle    400904 <main+0x1fa>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:57
  40092d:	83 45 9c 01          	addl   $0x1,-0x64(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:57 (discriminator 1)
  400931:	83 7d 9c 05          	cmpl   $0x5,-0x64(%rbp)
  400935:	7e c4                	jle    4008fb <main+0x1f1>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:65
  400937:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  40093b:	48 89 c7             	mov    %rax,%rdi
  40093e:	e8 1d fc ff ff       	callq  400560 <free@plt>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:70
  400943:	bf 0a 00 00 00       	mov    $0xa,%edi
  400948:	e8 83 fc ff ff       	callq  4005d0 <malloc@plt>
  40094d:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:71
  400951:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  400955:	ba 0a 00 00 00       	mov    $0xa,%edx
  40095a:	48 89 c6             	mov    %rax,%rsi
  40095d:	bf 01 00 00 00       	mov    $0x1,%edi
  400962:	e8 19 fc ff ff       	callq  400580 <write@plt>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:72
  400967:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  40096b:	48 83 c0 01          	add    $0x1,%rax
  40096f:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:73
  400973:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  400977:	48 bb 6f 76 65 72 77 	movabs $0x746972777265766f,%rbx
  40097e:	72 69 74 
  400981:	48 89 18             	mov    %rbx,(%rax)
  400984:	66 c7 40 08 65 00    	movw   $0x65,0x8(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:74
  40098a:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  40098e:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  400992:	48 89 d6             	mov    %rdx,%rsi
  400995:	48 89 c7             	mov    %rax,%rdi
  400998:	e8 d3 fb ff ff       	callq  400570 <strcpy@plt>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:75
  40099d:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  4009a1:	48 89 c7             	mov    %rax,%rdi
  4009a4:	e8 b7 fb ff ff       	callq  400560 <free@plt>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:77
  4009a9:	48 b8 00 00 00 00 00 	movabs $0x8000000000000000,%rax
  4009b0:	00 00 80 
  4009b3:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:78
  4009b7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  4009bb:	48 89 c7             	mov    %rax,%rdi
  4009be:	e8 0d fc ff ff       	callq  4005d0 <malloc@plt>
  4009c3:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:80
  4009c7:	c7 45 a4 00 00 00 00 	movl   $0x0,-0x5c(%rbp)
  4009ce:	eb 20                	jmp    4009f0 <main+0x2e6>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:81 (discriminator 2)
  4009d0:	8b 45 a4             	mov    -0x5c(%rbp),%eax
  4009d3:	48 63 d0             	movslq %eax,%rdx
  4009d6:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  4009da:	48 01 d0             	add    %rdx,%rax
  4009dd:	c6 00 63             	movb   $0x63,(%rax)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:82 (discriminator 2)
  4009e0:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  4009e4:	48 89 c7             	mov    %rax,%rdi
  4009e7:	e8 74 fb ff ff       	callq  400560 <free@plt>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:80 (discriminator 2)
  4009ec:	83 45 a4 01          	addl   $0x1,-0x5c(%rbp)
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:80 (discriminator 1)
  4009f0:	83 7d a4 09          	cmpl   $0x9,-0x5c(%rbp)
  4009f4:	7e da                	jle    4009d0 <main+0x2c6>
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:85
  4009f6:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  4009fa:	c7 00 00 00 10 00    	movl   $0x100000,(%rax)
  400a00:	b8 00 00 00 00       	mov    $0x0,%eax
/home/bhuvan/super_debugger/honorsProjekt/testers/test.c:87
  400a05:	48 83 c4 68          	add    $0x68,%rsp
  400a09:	5b                   	pop    %rbx
  400a0a:	5d                   	pop    %rbp
  400a0b:	c3                   	retq   
  400a0c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400a10 <__libc_csu_init>:
__libc_csu_init():
  400a10:	41 57                	push   %r15
  400a12:	41 89 ff             	mov    %edi,%r15d
  400a15:	41 56                	push   %r14
  400a17:	49 89 f6             	mov    %rsi,%r14
  400a1a:	41 55                	push   %r13
  400a1c:	49 89 d5             	mov    %rdx,%r13
  400a1f:	41 54                	push   %r12
  400a21:	4c 8d 25 e8 03 20 00 	lea    0x2003e8(%rip),%r12        # 600e10 <__frame_dummy_init_array_entry>
  400a28:	55                   	push   %rbp
  400a29:	48 8d 2d e8 03 20 00 	lea    0x2003e8(%rip),%rbp        # 600e18 <__init_array_end>
  400a30:	53                   	push   %rbx
  400a31:	4c 29 e5             	sub    %r12,%rbp
  400a34:	31 db                	xor    %ebx,%ebx
  400a36:	48 c1 fd 03          	sar    $0x3,%rbp
  400a3a:	48 83 ec 08          	sub    $0x8,%rsp
  400a3e:	e8 e5 fa ff ff       	callq  400528 <_init>
  400a43:	48 85 ed             	test   %rbp,%rbp
  400a46:	74 1e                	je     400a66 <__libc_csu_init+0x56>
  400a48:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  400a4f:	00 
  400a50:	4c 89 ea             	mov    %r13,%rdx
  400a53:	4c 89 f6             	mov    %r14,%rsi
  400a56:	44 89 ff             	mov    %r15d,%edi
  400a59:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  400a5d:	48 83 c3 01          	add    $0x1,%rbx
  400a61:	48 39 eb             	cmp    %rbp,%rbx
  400a64:	75 ea                	jne    400a50 <__libc_csu_init+0x40>
  400a66:	48 83 c4 08          	add    $0x8,%rsp
  400a6a:	5b                   	pop    %rbx
  400a6b:	5d                   	pop    %rbp
  400a6c:	41 5c                	pop    %r12
  400a6e:	41 5d                	pop    %r13
  400a70:	41 5e                	pop    %r14
  400a72:	41 5f                	pop    %r15
  400a74:	c3                   	retq   
  400a75:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  400a7c:	00 00 00 00 

0000000000400a80 <__libc_csu_fini>:
__libc_csu_fini():
  400a80:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400a84 <_fini>:
_fini():
  400a84:	48 83 ec 08          	sub    $0x8,%rsp
  400a88:	48 83 c4 08          	add    $0x8,%rsp
  400a8c:	c3                   	retq   
