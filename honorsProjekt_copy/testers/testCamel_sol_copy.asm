
./testers/testCamel_sol:     file format elf64-x86-64


Disassembly of section .init:

0000000000400500 <_init>:
_init():
  400500:	48 83 ec 08          	sub    $0x8,%rsp
  400504:	48 8b 05 ed 2a 20 00 	mov    0x202aed(%rip),%rax        # 602ff8 <_DYNAMIC+0x1d0>
  40050b:	48 85 c0             	test   %rax,%rax
  40050e:	74 05                	je     400515 <_init+0x15>
  400510:	e8 7b 00 00 00       	callq  400590 <__gmon_start__@plt>
  400515:	48 83 c4 08          	add    $0x8,%rsp
  400519:	c3                   	retq   

Disassembly of section .plt:

0000000000400520 <free@plt-0x10>:
  400520:	ff 35 e2 2a 20 00    	pushq  0x202ae2(%rip)        # 603008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400526:	ff 25 e4 2a 20 00    	jmpq   *0x202ae4(%rip)        # 603010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40052c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400530 <free@plt>:
  400530:	ff 25 e2 2a 20 00    	jmpq   *0x202ae2(%rip)        # 603018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400536:	68 00 00 00 00       	pushq  $0x0
  40053b:	e9 e0 ff ff ff       	jmpq   400520 <_init+0x20>

0000000000400540 <puts@plt>:
  400540:	ff 25 da 2a 20 00    	jmpq   *0x202ada(%rip)        # 603020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400546:	68 01 00 00 00       	pushq  $0x1
  40054b:	e9 d0 ff ff ff       	jmpq   400520 <_init+0x20>

0000000000400550 <strlen@plt>:
  400550:	ff 25 d2 2a 20 00    	jmpq   *0x202ad2(%rip)        # 603028 <_GLOBAL_OFFSET_TABLE_+0x28>
  400556:	68 02 00 00 00       	pushq  $0x2
  40055b:	e9 c0 ff ff ff       	jmpq   400520 <_init+0x20>

0000000000400560 <ispunct@plt>:
  400560:	ff 25 ca 2a 20 00    	jmpq   *0x202aca(%rip)        # 603030 <_GLOBAL_OFFSET_TABLE_+0x30>
  400566:	68 03 00 00 00       	pushq  $0x3
  40056b:	e9 b0 ff ff ff       	jmpq   400520 <_init+0x20>

0000000000400570 <isspace@plt>:
  400570:	ff 25 c2 2a 20 00    	jmpq   *0x202ac2(%rip)        # 603038 <_GLOBAL_OFFSET_TABLE_+0x38>
  400576:	68 04 00 00 00       	pushq  $0x4
  40057b:	e9 a0 ff ff ff       	jmpq   400520 <_init+0x20>

0000000000400580 <__libc_start_main@plt>:
  400580:	ff 25 ba 2a 20 00    	jmpq   *0x202aba(%rip)        # 603040 <_GLOBAL_OFFSET_TABLE_+0x40>
  400586:	68 05 00 00 00       	pushq  $0x5
  40058b:	e9 90 ff ff ff       	jmpq   400520 <_init+0x20>

0000000000400590 <__gmon_start__@plt>:
  400590:	ff 25 b2 2a 20 00    	jmpq   *0x202ab2(%rip)        # 603048 <_GLOBAL_OFFSET_TABLE_+0x48>
  400596:	68 06 00 00 00       	pushq  $0x6
  40059b:	e9 80 ff ff ff       	jmpq   400520 <_init+0x20>

00000000004005a0 <malloc@plt>:
  4005a0:	ff 25 aa 2a 20 00    	jmpq   *0x202aaa(%rip)        # 603050 <_GLOBAL_OFFSET_TABLE_+0x50>
  4005a6:	68 07 00 00 00       	pushq  $0x7
  4005ab:	e9 70 ff ff ff       	jmpq   400520 <_init+0x20>

Disassembly of section .text:

00000000004005b0 <_start>:
_start():
  4005b0:	31 ed                	xor    %ebp,%ebp
  4005b2:	49 89 d1             	mov    %rdx,%r9
  4005b5:	5e                   	pop    %rsi
  4005b6:	48 89 e2             	mov    %rsp,%rdx
  4005b9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4005bd:	50                   	push   %rax
  4005be:	54                   	push   %rsp
  4005bf:	49 c7 c0 e0 16 40 00 	mov    $0x4016e0,%r8
  4005c6:	48 c7 c1 70 16 40 00 	mov    $0x401670,%rcx
  4005cd:	48 c7 c7 35 16 40 00 	mov    $0x401635,%rdi
  4005d4:	e8 a7 ff ff ff       	callq  400580 <__libc_start_main@plt>
  4005d9:	f4                   	hlt    
  4005da:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000004005e0 <deregister_tm_clones>:
deregister_tm_clones():
  4005e0:	b8 6f 30 60 00       	mov    $0x60306f,%eax
  4005e5:	55                   	push   %rbp
  4005e6:	48 2d 68 30 60 00    	sub    $0x603068,%rax
  4005ec:	48 83 f8 0e          	cmp    $0xe,%rax
  4005f0:	48 89 e5             	mov    %rsp,%rbp
  4005f3:	77 02                	ja     4005f7 <deregister_tm_clones+0x17>
  4005f5:	5d                   	pop    %rbp
  4005f6:	c3                   	retq   
  4005f7:	b8 00 00 00 00       	mov    $0x0,%eax
  4005fc:	48 85 c0             	test   %rax,%rax
  4005ff:	74 f4                	je     4005f5 <deregister_tm_clones+0x15>
  400601:	5d                   	pop    %rbp
  400602:	bf 68 30 60 00       	mov    $0x603068,%edi
  400607:	ff e0                	jmpq   *%rax
  400609:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400610 <register_tm_clones>:
register_tm_clones():
  400610:	b8 68 30 60 00       	mov    $0x603068,%eax
  400615:	55                   	push   %rbp
  400616:	48 2d 68 30 60 00    	sub    $0x603068,%rax
  40061c:	48 c1 f8 03          	sar    $0x3,%rax
  400620:	48 89 e5             	mov    %rsp,%rbp
  400623:	48 89 c2             	mov    %rax,%rdx
  400626:	48 c1 ea 3f          	shr    $0x3f,%rdx
  40062a:	48 01 d0             	add    %rdx,%rax
  40062d:	48 d1 f8             	sar    %rax
  400630:	75 02                	jne    400634 <register_tm_clones+0x24>
  400632:	5d                   	pop    %rbp
  400633:	c3                   	retq   
  400634:	ba 00 00 00 00       	mov    $0x0,%edx
  400639:	48 85 d2             	test   %rdx,%rdx
  40063c:	74 f4                	je     400632 <register_tm_clones+0x22>
  40063e:	5d                   	pop    %rbp
  40063f:	48 89 c6             	mov    %rax,%rsi
  400642:	bf 68 30 60 00       	mov    $0x603068,%edi
  400647:	ff e2                	jmpq   *%rdx
  400649:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400650 <__do_global_dtors_aux>:
__do_global_dtors_aux():
  400650:	80 3d 11 2a 20 00 00 	cmpb   $0x0,0x202a11(%rip)        # 603068 <__TMC_END__>
  400657:	75 11                	jne    40066a <__do_global_dtors_aux+0x1a>
  400659:	55                   	push   %rbp
  40065a:	48 89 e5             	mov    %rsp,%rbp
  40065d:	e8 7e ff ff ff       	callq  4005e0 <deregister_tm_clones>
  400662:	5d                   	pop    %rbp
  400663:	c6 05 fe 29 20 00 01 	movb   $0x1,0x2029fe(%rip)        # 603068 <__TMC_END__>
  40066a:	f3 c3                	repz retq 
  40066c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400670 <frame_dummy>:
frame_dummy():
  400670:	48 83 3d a8 27 20 00 	cmpq   $0x0,0x2027a8(%rip)        # 602e20 <__JCR_END__>
  400677:	00 
  400678:	74 1e                	je     400698 <frame_dummy+0x28>
  40067a:	b8 00 00 00 00       	mov    $0x0,%eax
  40067f:	48 85 c0             	test   %rax,%rax
  400682:	74 14                	je     400698 <frame_dummy+0x28>
  400684:	55                   	push   %rbp
  400685:	bf 20 2e 60 00       	mov    $0x602e20,%edi
  40068a:	48 89 e5             	mov    %rsp,%rbp
  40068d:	ff d0                	callq  *%rax
  40068f:	5d                   	pop    %rbp
  400690:	e9 7b ff ff ff       	jmpq   400610 <register_tm_clones>
  400695:	0f 1f 00             	nopl   (%rax)
  400698:	e9 73 ff ff ff       	jmpq   400610 <register_tm_clones>

000000000040069d <strCompare>:
strCompare():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:7
  40069d:	55                   	push   %rbp
  40069e:	48 89 e5             	mov    %rsp,%rbp
  4006a1:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  4006a5:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:8
  4006a9:	eb 2e                	jmp    4006d9 <strCompare+0x3c>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:9
  4006ab:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4006af:	0f b6 00             	movzbl (%rax),%eax
  4006b2:	84 c0                	test   %al,%al
  4006b4:	74 19                	je     4006cf <strCompare+0x32>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:10
  4006b6:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4006ba:	0f b6 10             	movzbl (%rax),%edx
  4006bd:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4006c1:	0f b6 00             	movzbl (%rax),%eax
  4006c4:	38 c2                	cmp    %al,%dl
  4006c6:	74 07                	je     4006cf <strCompare+0x32>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:11
  4006c8:	b8 00 00 00 00       	mov    $0x0,%eax
  4006cd:	eb 2c                	jmp    4006fb <strCompare+0x5e>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:14
  4006cf:	48 83 45 f8 01       	addq   $0x1,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:15
  4006d4:	48 83 45 f0 01       	addq   $0x1,-0x10(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:8 (discriminator 1)
  4006d9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4006dd:	0f b6 00             	movzbl (%rax),%eax
  4006e0:	84 c0                	test   %al,%al
  4006e2:	75 c7                	jne    4006ab <strCompare+0xe>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:18
  4006e4:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4006e8:	0f b6 00             	movzbl (%rax),%eax
  4006eb:	84 c0                	test   %al,%al
  4006ed:	75 07                	jne    4006f6 <strCompare+0x59>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:19
  4006ef:	b8 01 00 00 00       	mov    $0x1,%eax
  4006f4:	eb 05                	jmp    4006fb <strCompare+0x5e>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:20
  4006f6:	b8 00 00 00 00       	mov    $0x0,%eax
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:21
  4006fb:	5d                   	pop    %rbp
  4006fc:	c3                   	retq   

00000000004006fd <equal>:
equal():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:24
  4006fd:	55                   	push   %rbp
  4006fe:	48 89 e5             	mov    %rsp,%rbp
  400701:	48 83 ec 28          	sub    $0x28,%rsp
  400705:	89 7d ec             	mov    %edi,-0x14(%rbp)
  400708:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
  40070c:	48 89 55 d8          	mov    %rdx,-0x28(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:25
  400710:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  400715:	75 0a                	jne    400721 <equal+0x24>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:26
  400717:	b8 00 00 00 00       	mov    $0x0,%eax
  40071c:	e9 da 00 00 00       	jmpq   4007fb <equal+0xfe>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:28
  400721:	8b 45 ec             	mov    -0x14(%rbp),%eax
  400724:	48 98                	cltq   
  400726:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  40072d:	00 
  40072e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  400732:	48 01 d0             	add    %rdx,%rax
  400735:	48 8b 00             	mov    (%rax),%rax
  400738:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:30
  40073c:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:32
  400743:	eb 6e                	jmp    4007b3 <equal+0xb6>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:33
  400745:	8b 45 f4             	mov    -0xc(%rbp),%eax
  400748:	48 98                	cltq   
  40074a:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400751:	00 
  400752:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400756:	48 01 d0             	add    %rdx,%rax
  400759:	48 8b 00             	mov    (%rax),%rax
  40075c:	48 85 c0             	test   %rax,%rax
  40075f:	75 0a                	jne    40076b <equal+0x6e>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:34
  400761:	b8 00 00 00 00       	mov    $0x0,%eax
  400766:	e9 90 00 00 00       	jmpq   4007fb <equal+0xfe>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:36
  40076b:	8b 45 f4             	mov    -0xc(%rbp),%eax
  40076e:	48 98                	cltq   
  400770:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400777:	00 
  400778:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  40077c:	48 01 d0             	add    %rdx,%rax
  40077f:	48 8b 10             	mov    (%rax),%rdx
  400782:	8b 45 f4             	mov    -0xc(%rbp),%eax
  400785:	48 98                	cltq   
  400787:	48 8d 0c c5 00 00 00 	lea    0x0(,%rax,8),%rcx
  40078e:	00 
  40078f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  400793:	48 01 c8             	add    %rcx,%rax
  400796:	48 8b 00             	mov    (%rax),%rax
  400799:	48 89 d6             	mov    %rdx,%rsi
  40079c:	48 89 c7             	mov    %rax,%rdi
  40079f:	e8 f9 fe ff ff       	callq  40069d <strCompare>
  4007a4:	85 c0                	test   %eax,%eax
  4007a6:	75 07                	jne    4007af <equal+0xb2>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:37
  4007a8:	b8 00 00 00 00       	mov    $0x0,%eax
  4007ad:	eb 4c                	jmp    4007fb <equal+0xfe>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:39
  4007af:	83 45 f4 01          	addl   $0x1,-0xc(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:32 (discriminator 1)
  4007b3:	8b 45 f4             	mov    -0xc(%rbp),%eax
  4007b6:	48 98                	cltq   
  4007b8:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4007bf:	00 
  4007c0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4007c4:	48 01 d0             	add    %rdx,%rax
  4007c7:	48 8b 00             	mov    (%rax),%rax
  4007ca:	48 85 c0             	test   %rax,%rax
  4007cd:	0f 85 72 ff ff ff    	jne    400745 <equal+0x48>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:42
  4007d3:	8b 45 f4             	mov    -0xc(%rbp),%eax
  4007d6:	48 98                	cltq   
  4007d8:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4007df:	00 
  4007e0:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  4007e4:	48 01 d0             	add    %rdx,%rax
  4007e7:	48 8b 00             	mov    (%rax),%rax
  4007ea:	48 85 c0             	test   %rax,%rax
  4007ed:	74 07                	je     4007f6 <equal+0xf9>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:43
  4007ef:	b8 00 00 00 00       	mov    $0x0,%eax
  4007f4:	eb 05                	jmp    4007fb <equal+0xfe>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:45
  4007f6:	b8 01 00 00 00       	mov    $0x1,%eax
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:46
  4007fb:	c9                   	leaveq 
  4007fc:	c3                   	retq   

00000000004007fd <test_camelCaser>:
test_camelCaser():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:49
  4007fd:	55                   	push   %rbp
  4007fe:	48 89 e5             	mov    %rsp,%rbp
  400801:	48 81 ec 10 04 00 00 	sub    $0x410,%rsp
  400808:	48 89 bd f8 fb ff ff 	mov    %rdi,-0x408(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:50
  40080f:	48 8d 95 70 ff ff ff 	lea    -0x90(%rbp),%rdx
  400816:	be e0 1e 40 00       	mov    $0x401ee0,%esi
  40081b:	b8 11 00 00 00       	mov    $0x11,%eax
  400820:	48 89 d7             	mov    %rdx,%rdi
  400823:	48 89 c1             	mov    %rax,%rcx
  400826:	f3 48 a5             	rep movsq %ds:(%rsi),%es:(%rdi)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:72
  400829:	48 c7 85 50 fc ff ff 	movq   $0x401720,-0x3b0(%rbp)
  400830:	20 17 40 00 
  400834:	48 c7 85 58 fc ff ff 	movq   $0x401755,-0x3a8(%rbp)
  40083b:	55 17 40 00 
  40083f:	48 c7 85 60 fc ff ff 	movq   $0x0,-0x3a0(%rbp)
  400846:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:78
  40084a:	48 c7 85 f0 fe ff ff 	movq   $0x401771,-0x110(%rbp)
  400851:	71 17 40 00 
  400855:	48 c7 85 f8 fe ff ff 	movq   $0x401771,-0x108(%rbp)
  40085c:	71 17 40 00 
  400860:	48 c7 85 00 ff ff ff 	movq   $0x401771,-0x100(%rbp)
  400867:	71 17 40 00 
  40086b:	48 c7 85 08 ff ff ff 	movq   $0x401771,-0xf8(%rbp)
  400872:	71 17 40 00 
  400876:	48 c7 85 10 ff ff ff 	movq   $0x401771,-0xf0(%rbp)
  40087d:	71 17 40 00 
  400881:	48 c7 85 18 ff ff ff 	movq   $0x401771,-0xe8(%rbp)
  400888:	71 17 40 00 
  40088c:	48 c7 85 20 ff ff ff 	movq   $0x401771,-0xe0(%rbp)
  400893:	71 17 40 00 
  400897:	48 c7 85 28 ff ff ff 	movq   $0x401772,-0xd8(%rbp)
  40089e:	72 17 40 00 
  4008a2:	48 c7 85 30 ff ff ff 	movq   $0x401771,-0xd0(%rbp)
  4008a9:	71 17 40 00 
  4008ad:	48 c7 85 38 ff ff ff 	movq   $0x401771,-0xc8(%rbp)
  4008b4:	71 17 40 00 
  4008b8:	48 c7 85 40 ff ff ff 	movq   $0x401771,-0xc0(%rbp)
  4008bf:	71 17 40 00 
  4008c3:	48 c7 85 48 ff ff ff 	movq   $0x401771,-0xb8(%rbp)
  4008ca:	71 17 40 00 
  4008ce:	48 c7 85 50 ff ff ff 	movq   $0x401771,-0xb0(%rbp)
  4008d5:	71 17 40 00 
  4008d9:	48 c7 85 58 ff ff ff 	movq   $0x401771,-0xa8(%rbp)
  4008e0:	71 17 40 00 
  4008e4:	48 c7 85 60 ff ff ff 	movq   $0x0,-0xa0(%rbp)
  4008eb:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:96
  4008ef:	48 c7 85 20 fe ff ff 	movq   $0x401771,-0x1e0(%rbp)
  4008f6:	71 17 40 00 
  4008fa:	48 c7 85 28 fe ff ff 	movq   $0x401771,-0x1d8(%rbp)
  400901:	71 17 40 00 
  400905:	48 c7 85 30 fe ff ff 	movq   $0x401771,-0x1d0(%rbp)
  40090c:	71 17 40 00 
  400910:	48 c7 85 38 fe ff ff 	movq   $0x401771,-0x1c8(%rbp)
  400917:	71 17 40 00 
  40091b:	48 c7 85 40 fe ff ff 	movq   $0x401771,-0x1c0(%rbp)
  400922:	71 17 40 00 
  400926:	48 c7 85 48 fe ff ff 	movq   $0x40177a,-0x1b8(%rbp)
  40092d:	7a 17 40 00 
  400931:	48 c7 85 50 fe ff ff 	movq   $0x401785,-0x1b0(%rbp)
  400938:	85 17 40 00 
  40093c:	48 c7 85 58 fe ff ff 	movq   $0x40178b,-0x1a8(%rbp)
  400943:	8b 17 40 00 
  400947:	48 c7 85 60 fe ff ff 	movq   $0x401791,-0x1a0(%rbp)
  40094e:	91 17 40 00 
  400952:	48 c7 85 68 fe ff ff 	movq   $0x401797,-0x198(%rbp)
  400959:	97 17 40 00 
  40095d:	48 c7 85 70 fe ff ff 	movq   $0x0,-0x190(%rbp)
  400964:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:110
  400968:	48 c7 85 50 fd ff ff 	movq   $0x40179d,-0x2b0(%rbp)
  40096f:	9d 17 40 00 
  400973:	48 c7 85 58 fd ff ff 	movq   $0x4017b7,-0x2a8(%rbp)
  40097a:	b7 17 40 00 
  40097e:	48 c7 85 60 fd ff ff 	movq   $0x4017c3,-0x2a0(%rbp)
  400985:	c3 17 40 00 
  400989:	48 c7 85 68 fd ff ff 	movq   $0x4017c6,-0x298(%rbp)
  400990:	c6 17 40 00 
  400994:	48 c7 85 70 fd ff ff 	movq   $0x4017d2,-0x290(%rbp)
  40099b:	d2 17 40 00 
  40099f:	48 c7 85 78 fd ff ff 	movq   $0x0,-0x288(%rbp)
  4009a6:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:119
  4009aa:	48 c7 85 90 fc ff ff 	movq   $0x4017db,-0x370(%rbp)
  4009b1:	db 17 40 00 
  4009b5:	48 c7 85 98 fc ff ff 	movq   $0x4017e0,-0x368(%rbp)
  4009bc:	e0 17 40 00 
  4009c0:	48 c7 85 a0 fc ff ff 	movq   $0x4017ef,-0x360(%rbp)
  4009c7:	ef 17 40 00 
  4009cb:	48 c7 85 a8 fc ff ff 	movq   $0x0,-0x358(%rbp)
  4009d2:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:126
  4009d6:	48 c7 85 e0 fd ff ff 	movq   $0x4017f5,-0x220(%rbp)
  4009dd:	f5 17 40 00 
  4009e1:	48 c7 85 e8 fd ff ff 	movq   $0x4017f7,-0x218(%rbp)
  4009e8:	f7 17 40 00 
  4009ec:	48 c7 85 f0 fd ff ff 	movq   $0x4017f9,-0x210(%rbp)
  4009f3:	f9 17 40 00 
  4009f7:	48 c7 85 f8 fd ff ff 	movq   $0x4017f7,-0x208(%rbp)
  4009fe:	f7 17 40 00 
  400a02:	48 c7 85 00 fe ff ff 	movq   $0x4017fb,-0x200(%rbp)
  400a09:	fb 17 40 00 
  400a0d:	48 c7 85 08 fe ff ff 	movq   $0x4017f7,-0x1f8(%rbp)
  400a14:	f7 17 40 00 
  400a18:	48 c7 85 10 fe ff ff 	movq   $0x4017fd,-0x1f0(%rbp)
  400a1f:	fd 17 40 00 
  400a23:	48 c7 85 18 fe ff ff 	movq   $0x0,-0x1e8(%rbp)
  400a2a:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:137
  400a2e:	48 c7 85 80 fd ff ff 	movq   $0x40180b,-0x280(%rbp)
  400a35:	0b 18 40 00 
  400a39:	48 c7 85 88 fd ff ff 	movq   $0x401820,-0x278(%rbp)
  400a40:	20 18 40 00 
  400a44:	48 c7 85 90 fd ff ff 	movq   $0x40182e,-0x270(%rbp)
  400a4b:	2e 18 40 00 
  400a4f:	48 c7 85 98 fd ff ff 	movq   $0x40183e,-0x268(%rbp)
  400a56:	3e 18 40 00 
  400a5a:	48 c7 85 a0 fd ff ff 	movq   $0x40184b,-0x260(%rbp)
  400a61:	4b 18 40 00 
  400a65:	48 c7 85 a8 fd ff ff 	movq   $0x0,-0x258(%rbp)
  400a6c:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:147
  400a70:	48 c7 85 80 fe ff ff 	movq   $0x401771,-0x180(%rbp)
  400a77:	71 17 40 00 
  400a7b:	48 c7 85 88 fe ff ff 	movq   $0x401771,-0x178(%rbp)
  400a82:	71 17 40 00 
  400a86:	48 c7 85 90 fe ff ff 	movq   $0x40185b,-0x170(%rbp)
  400a8d:	5b 18 40 00 
  400a91:	48 c7 85 98 fe ff ff 	movq   $0x401771,-0x168(%rbp)
  400a98:	71 17 40 00 
  400a9c:	48 c7 85 a0 fe ff ff 	movq   $0x401771,-0x160(%rbp)
  400aa3:	71 17 40 00 
  400aa7:	48 c7 85 a8 fe ff ff 	movq   $0x401771,-0x158(%rbp)
  400aae:	71 17 40 00 
  400ab2:	48 c7 85 b0 fe ff ff 	movq   $0x401771,-0x150(%rbp)
  400ab9:	71 17 40 00 
  400abd:	48 c7 85 b8 fe ff ff 	movq   $0x401771,-0x148(%rbp)
  400ac4:	71 17 40 00 
  400ac8:	48 c7 85 c0 fe ff ff 	movq   $0x401771,-0x140(%rbp)
  400acf:	71 17 40 00 
  400ad3:	48 c7 85 c8 fe ff ff 	movq   $0x40186a,-0x138(%rbp)
  400ada:	6a 18 40 00 
  400ade:	48 c7 85 d0 fe ff ff 	movq   $0x40186e,-0x130(%rbp)
  400ae5:	6e 18 40 00 
  400ae9:	48 c7 85 d8 fe ff ff 	movq   $0x401771,-0x128(%rbp)
  400af0:	71 17 40 00 
  400af4:	48 c7 85 e0 fe ff ff 	movq   $0x40187b,-0x120(%rbp)
  400afb:	7b 18 40 00 
  400aff:	48 c7 85 e8 fe ff ff 	movq   $0x0,-0x118(%rbp)
  400b06:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:164
  400b0a:	48 c7 85 b0 fc ff ff 	movq   $0x401885,-0x350(%rbp)
  400b11:	85 18 40 00 
  400b15:	48 c7 85 b8 fc ff ff 	movq   $0x401887,-0x348(%rbp)
  400b1c:	87 18 40 00 
  400b20:	48 c7 85 c0 fc ff ff 	movq   $0x40188a,-0x340(%rbp)
  400b27:	8a 18 40 00 
  400b2b:	48 c7 85 c8 fc ff ff 	movq   $0x0,-0x338(%rbp)
  400b32:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:171
  400b36:	48 c7 85 d0 fc ff ff 	movq   $0x401771,-0x330(%rbp)
  400b3d:	71 17 40 00 
  400b41:	48 c7 85 d8 fc ff ff 	movq   $0x401771,-0x328(%rbp)
  400b48:	71 17 40 00 
  400b4c:	48 c7 85 e0 fc ff ff 	movq   $0x4018a8,-0x320(%rbp)
  400b53:	a8 18 40 00 
  400b57:	48 c7 85 e8 fc ff ff 	movq   $0x0,-0x318(%rbp)
  400b5e:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:178
  400b62:	48 c7 85 f0 fc ff ff 	movq   $0x4018ae,-0x310(%rbp)
  400b69:	ae 18 40 00 
  400b6d:	48 c7 85 f8 fc ff ff 	movq   $0x4018c1,-0x308(%rbp)
  400b74:	c1 18 40 00 
  400b78:	48 c7 85 00 fd ff ff 	movq   $0x4018d6,-0x300(%rbp)
  400b7f:	d6 18 40 00 
  400b83:	48 c7 85 08 fd ff ff 	movq   $0x0,-0x2f8(%rbp)
  400b8a:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:185
  400b8e:	48 c7 85 10 fd ff ff 	movq   $0x4018f0,-0x2f0(%rbp)
  400b95:	f0 18 40 00 
  400b99:	48 c7 85 18 fd ff ff 	movq   $0x40190e,-0x2e8(%rbp)
  400ba0:	0e 19 40 00 
  400ba4:	48 c7 85 20 fd ff ff 	movq   $0x401771,-0x2e0(%rbp)
  400bab:	71 17 40 00 
  400baf:	48 c7 85 28 fd ff ff 	movq   $0x0,-0x2d8(%rbp)
  400bb6:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:192
  400bba:	48 c7 85 70 fc ff ff 	movq   $0x401928,-0x390(%rbp)
  400bc1:	28 19 40 00 
  400bc5:	48 c7 85 78 fc ff ff 	movq   $0x401943,-0x388(%rbp)
  400bcc:	43 19 40 00 
  400bd0:	48 c7 85 80 fc ff ff 	movq   $0x0,-0x380(%rbp)
  400bd7:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:198
  400bdb:	48 c7 85 b0 fd ff ff 	movq   $0x401771,-0x250(%rbp)
  400be2:	71 17 40 00 
  400be6:	48 c7 85 b8 fd ff ff 	movq   $0x401959,-0x248(%rbp)
  400bed:	59 19 40 00 
  400bf1:	48 c7 85 c0 fd ff ff 	movq   $0x401968,-0x240(%rbp)
  400bf8:	68 19 40 00 
  400bfc:	48 c7 85 c8 fd ff ff 	movq   $0x401975,-0x238(%rbp)
  400c03:	75 19 40 00 
  400c07:	48 c7 85 d0 fd ff ff 	movq   $0x401993,-0x230(%rbp)
  400c0e:	93 19 40 00 
  400c12:	48 c7 85 d8 fd ff ff 	movq   $0x0,-0x228(%rbp)
  400c19:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:207
  400c1d:	48 c7 85 40 fc ff ff 	movq   $0x4019ae,-0x3c0(%rbp)
  400c24:	ae 19 40 00 
  400c28:	48 c7 85 48 fc ff ff 	movq   $0x0,-0x3b8(%rbp)
  400c2f:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:212
  400c33:	48 c7 85 30 fd ff ff 	movq   $0x4019c2,-0x2d0(%rbp)
  400c3a:	c2 19 40 00 
  400c3e:	48 c7 85 38 fd ff ff 	movq   $0x4019d4,-0x2c8(%rbp)
  400c45:	d4 19 40 00 
  400c49:	48 c7 85 40 fd ff ff 	movq   $0x4019ed,-0x2c0(%rbp)
  400c50:	ed 19 40 00 
  400c54:	48 c7 85 48 fd ff ff 	movq   $0x0,-0x2b8(%rbp)
  400c5b:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:219
  400c5f:	bf 80 00 00 00       	mov    $0x80,%edi
  400c64:	e8 37 f9 ff ff       	callq  4005a0 <malloc@plt>
  400c69:	48 89 85 20 fc ff ff 	mov    %rax,-0x3e0(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:221
  400c70:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400c77:	48 8d 95 50 fc ff ff 	lea    -0x3b0(%rbp),%rdx
  400c7e:	48 89 10             	mov    %rdx,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:222
  400c81:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400c88:	48 8d 50 08          	lea    0x8(%rax),%rdx
  400c8c:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
  400c93:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:223
  400c96:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400c9d:	48 8d 50 10          	lea    0x10(%rax),%rdx
  400ca1:	48 8d 85 20 fe ff ff 	lea    -0x1e0(%rbp),%rax
  400ca8:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:224
  400cab:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400cb2:	48 8d 50 18          	lea    0x18(%rax),%rdx
  400cb6:	48 8d 85 50 fd ff ff 	lea    -0x2b0(%rbp),%rax
  400cbd:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:225
  400cc0:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400cc7:	48 8d 50 20          	lea    0x20(%rax),%rdx
  400ccb:	48 8d 85 90 fc ff ff 	lea    -0x370(%rbp),%rax
  400cd2:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:226
  400cd5:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400cdc:	48 8d 50 28          	lea    0x28(%rax),%rdx
  400ce0:	48 8d 85 e0 fd ff ff 	lea    -0x220(%rbp),%rax
  400ce7:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:227
  400cea:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400cf1:	48 8d 50 30          	lea    0x30(%rax),%rdx
  400cf5:	48 8d 85 80 fd ff ff 	lea    -0x280(%rbp),%rax
  400cfc:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:228
  400cff:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400d06:	48 8d 50 38          	lea    0x38(%rax),%rdx
  400d0a:	48 8d 85 80 fe ff ff 	lea    -0x180(%rbp),%rax
  400d11:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:229
  400d14:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400d1b:	48 8d 50 40          	lea    0x40(%rax),%rdx
  400d1f:	48 8d 85 b0 fc ff ff 	lea    -0x350(%rbp),%rax
  400d26:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:230
  400d29:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400d30:	48 8d 50 48          	lea    0x48(%rax),%rdx
  400d34:	48 8d 85 d0 fc ff ff 	lea    -0x330(%rbp),%rax
  400d3b:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:231
  400d3e:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400d45:	48 8d 50 50          	lea    0x50(%rax),%rdx
  400d49:	48 8d 85 f0 fc ff ff 	lea    -0x310(%rbp),%rax
  400d50:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:232
  400d53:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400d5a:	48 8d 50 58          	lea    0x58(%rax),%rdx
  400d5e:	48 8d 85 10 fd ff ff 	lea    -0x2f0(%rbp),%rax
  400d65:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:233
  400d68:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400d6f:	48 8d 50 60          	lea    0x60(%rax),%rdx
  400d73:	48 8d 85 70 fc ff ff 	lea    -0x390(%rbp),%rax
  400d7a:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:234
  400d7d:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400d84:	48 8d 50 68          	lea    0x68(%rax),%rdx
  400d88:	48 8d 85 b0 fd ff ff 	lea    -0x250(%rbp),%rax
  400d8f:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:235
  400d92:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400d99:	48 8d 50 70          	lea    0x70(%rax),%rdx
  400d9d:	48 8d 85 40 fc ff ff 	lea    -0x3c0(%rbp),%rax
  400da4:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:236
  400da7:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400dae:	48 8d 50 78          	lea    0x78(%rax),%rdx
  400db2:	48 8d 85 30 fd ff ff 	lea    -0x2d0(%rbp),%rax
  400db9:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:241
  400dbc:	48 8d 85 70 ff ff ff 	lea    -0x90(%rbp),%rax
  400dc3:	48 89 85 08 fc ff ff 	mov    %rax,-0x3f8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:242
  400dca:	c7 85 04 fc ff ff 00 	movl   $0x0,-0x3fc(%rbp)
  400dd1:	00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:243
  400dd4:	e9 29 01 00 00       	jmpq   400f02 <test_camelCaser+0x705>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:244
  400dd9:	48 8b 85 08 fc ff ff 	mov    -0x3f8(%rbp),%rax
  400de0:	48 8b 10             	mov    (%rax),%rdx
  400de3:	48 8b 85 f8 fb ff ff 	mov    -0x408(%rbp),%rax
  400dea:	48 89 d7             	mov    %rdx,%rdi
  400ded:	ff d0                	callq  *%rax
  400def:	48 89 85 10 fc ff ff 	mov    %rax,-0x3f0(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:245
  400df6:	48 8b 95 20 fc ff ff 	mov    -0x3e0(%rbp),%rdx
  400dfd:	48 8b 8d 10 fc ff ff 	mov    -0x3f0(%rbp),%rcx
  400e04:	8b 85 04 fc ff ff    	mov    -0x3fc(%rbp),%eax
  400e0a:	48 89 ce             	mov    %rcx,%rsi
  400e0d:	89 c7                	mov    %eax,%edi
  400e0f:	e8 e9 f8 ff ff       	callq  4006fd <equal>
  400e14:	85 c0                	test   %eax,%eax
  400e16:	75 7a                	jne    400e92 <test_camelCaser+0x695>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:247
  400e18:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400e1f:	48 89 c7             	mov    %rax,%rdi
  400e22:	e8 09 f7 ff ff       	callq  400530 <free@plt>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:249
  400e27:	48 8b 85 10 fc ff ff 	mov    -0x3f0(%rbp),%rax
  400e2e:	48 89 85 28 fc ff ff 	mov    %rax,-0x3d8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:251
  400e35:	eb 28                	jmp    400e5f <test_camelCaser+0x662>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:252
  400e37:	48 8b 85 10 fc ff ff 	mov    -0x3f0(%rbp),%rax
  400e3e:	48 8b 00             	mov    (%rax),%rax
  400e41:	48 89 c7             	mov    %rax,%rdi
  400e44:	e8 e7 f6 ff ff       	callq  400530 <free@plt>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:253
  400e49:	48 8b 85 10 fc ff ff 	mov    -0x3f0(%rbp),%rax
  400e50:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:254
  400e57:	48 83 85 10 fc ff ff 	addq   $0x8,-0x3f0(%rbp)
  400e5e:	08 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:251 (discriminator 1)
  400e5f:	48 8b 85 10 fc ff ff 	mov    -0x3f0(%rbp),%rax
  400e66:	48 8b 00             	mov    (%rax),%rax
  400e69:	48 85 c0             	test   %rax,%rax
  400e6c:	75 c9                	jne    400e37 <test_camelCaser+0x63a>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:257
  400e6e:	48 8b 85 28 fc ff ff 	mov    -0x3d8(%rbp),%rax
  400e75:	48 89 c7             	mov    %rax,%rdi
  400e78:	e8 b3 f6 ff ff       	callq  400530 <free@plt>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:258
  400e7d:	48 c7 85 28 fc ff ff 	movq   $0x0,-0x3d8(%rbp)
  400e84:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:260
  400e88:	b8 00 00 00 00       	mov    $0x0,%eax
  400e8d:	e9 29 01 00 00       	jmpq   400fbb <test_camelCaser+0x7be>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:264
  400e92:	83 85 04 fc ff ff 01 	addl   $0x1,-0x3fc(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:265
  400e99:	48 83 85 08 fc ff ff 	addq   $0x8,-0x3f8(%rbp)
  400ea0:	08 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:267
  400ea1:	48 8b 85 10 fc ff ff 	mov    -0x3f0(%rbp),%rax
  400ea8:	48 89 85 30 fc ff ff 	mov    %rax,-0x3d0(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:269
  400eaf:	eb 28                	jmp    400ed9 <test_camelCaser+0x6dc>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:270
  400eb1:	48 8b 85 10 fc ff ff 	mov    -0x3f0(%rbp),%rax
  400eb8:	48 8b 00             	mov    (%rax),%rax
  400ebb:	48 89 c7             	mov    %rax,%rdi
  400ebe:	e8 6d f6 ff ff       	callq  400530 <free@plt>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:271
  400ec3:	48 8b 85 10 fc ff ff 	mov    -0x3f0(%rbp),%rax
  400eca:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:272
  400ed1:	48 83 85 10 fc ff ff 	addq   $0x8,-0x3f0(%rbp)
  400ed8:	08 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:269 (discriminator 1)
  400ed9:	48 8b 85 10 fc ff ff 	mov    -0x3f0(%rbp),%rax
  400ee0:	48 8b 00             	mov    (%rax),%rax
  400ee3:	48 85 c0             	test   %rax,%rax
  400ee6:	75 c9                	jne    400eb1 <test_camelCaser+0x6b4>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:275
  400ee8:	48 8b 85 30 fc ff ff 	mov    -0x3d0(%rbp),%rax
  400eef:	48 89 c7             	mov    %rax,%rdi
  400ef2:	e8 39 f6 ff ff       	callq  400530 <free@plt>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:276
  400ef7:	48 c7 85 30 fc ff ff 	movq   $0x0,-0x3d0(%rbp)
  400efe:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:243 (discriminator 1)
  400f02:	48 8b 85 08 fc ff ff 	mov    -0x3f8(%rbp),%rax
  400f09:	48 8b 00             	mov    (%rax),%rax
  400f0c:	48 85 c0             	test   %rax,%rax
  400f0f:	0f 85 c4 fe ff ff    	jne    400dd9 <test_camelCaser+0x5dc>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:279
  400f15:	48 8b 85 20 fc ff ff 	mov    -0x3e0(%rbp),%rax
  400f1c:	48 89 c7             	mov    %rax,%rdi
  400f1f:	e8 0c f6 ff ff       	callq  400530 <free@plt>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:280
  400f24:	48 c7 85 20 fc ff ff 	movq   $0x0,-0x3e0(%rbp)
  400f2b:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:282
  400f2f:	48 8b 85 f8 fb ff ff 	mov    -0x408(%rbp),%rax
  400f36:	bf 00 00 00 00       	mov    $0x0,%edi
  400f3b:	ff d0                	callq  *%rax
  400f3d:	48 89 85 18 fc ff ff 	mov    %rax,-0x3e8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:283
  400f44:	48 83 bd 18 fc ff ff 	cmpq   $0x0,-0x3e8(%rbp)
  400f4b:	00 
  400f4c:	74 68                	je     400fb6 <test_camelCaser+0x7b9>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:284
  400f4e:	48 8b 85 18 fc ff ff 	mov    -0x3e8(%rbp),%rax
  400f55:	48 89 85 38 fc ff ff 	mov    %rax,-0x3c8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:286
  400f5c:	eb 28                	jmp    400f86 <test_camelCaser+0x789>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:287
  400f5e:	48 8b 85 18 fc ff ff 	mov    -0x3e8(%rbp),%rax
  400f65:	48 8b 00             	mov    (%rax),%rax
  400f68:	48 89 c7             	mov    %rax,%rdi
  400f6b:	e8 c0 f5 ff ff       	callq  400530 <free@plt>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:288
  400f70:	48 8b 85 18 fc ff ff 	mov    -0x3e8(%rbp),%rax
  400f77:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:289
  400f7e:	48 83 85 18 fc ff ff 	addq   $0x8,-0x3e8(%rbp)
  400f85:	08 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:286 (discriminator 1)
  400f86:	48 8b 85 18 fc ff ff 	mov    -0x3e8(%rbp),%rax
  400f8d:	48 8b 00             	mov    (%rax),%rax
  400f90:	48 85 c0             	test   %rax,%rax
  400f93:	75 c9                	jne    400f5e <test_camelCaser+0x761>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:292
  400f95:	48 8b 85 38 fc ff ff 	mov    -0x3c8(%rbp),%rax
  400f9c:	48 89 c7             	mov    %rax,%rdi
  400f9f:	e8 8c f5 ff ff       	callq  400530 <free@plt>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:293
  400fa4:	48 c7 85 38 fc ff ff 	movq   $0x0,-0x3c8(%rbp)
  400fab:	00 00 00 00 
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:295
  400faf:	b8 00 00 00 00       	mov    $0x0,%eax
  400fb4:	eb 05                	jmp    400fbb <test_camelCaser+0x7be>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:298
  400fb6:	b8 01 00 00 00       	mov    $0x1,%eax
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:299
  400fbb:	c9                   	leaveq 
  400fbc:	c3                   	retq   

0000000000400fbd <findPunct>:
findPunct():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:307
  400fbd:	55                   	push   %rbp
  400fbe:	48 89 e5             	mov    %rsp,%rbp
  400fc1:	48 83 ec 20          	sub    $0x20,%rsp
  400fc5:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:308
  400fc9:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  400fcd:	48 89 c7             	mov    %rax,%rdi
  400fd0:	e8 7b f5 ff ff       	callq  400550 <strlen@plt>
  400fd5:	89 45 fc             	mov    %eax,-0x4(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:309
  400fd8:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:311
  400fdf:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
  400fe6:	eb 26                	jmp    40100e <findPunct+0x51>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:312
  400fe8:	8b 45 f8             	mov    -0x8(%rbp),%eax
  400feb:	48 63 d0             	movslq %eax,%rdx
  400fee:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  400ff2:	48 01 d0             	add    %rdx,%rax
  400ff5:	0f b6 00             	movzbl (%rax),%eax
  400ff8:	0f be c0             	movsbl %al,%eax
  400ffb:	89 c7                	mov    %eax,%edi
  400ffd:	e8 5e f5 ff ff       	callq  400560 <ispunct@plt>
  401002:	85 c0                	test   %eax,%eax
  401004:	74 04                	je     40100a <findPunct+0x4d>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:313
  401006:	83 45 f4 01          	addl   $0x1,-0xc(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:311
  40100a:	83 45 f8 01          	addl   $0x1,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:311 (discriminator 1)
  40100e:	8b 45 f8             	mov    -0x8(%rbp),%eax
  401011:	3b 45 fc             	cmp    -0x4(%rbp),%eax
  401014:	7c d2                	jl     400fe8 <findPunct+0x2b>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:316
  401016:	8b 45 f4             	mov    -0xc(%rbp),%eax
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:317
  401019:	c9                   	leaveq 
  40101a:	c3                   	retq   

000000000040101b <getSpaces>:
getSpaces():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:319
  40101b:	55                   	push   %rbp
  40101c:	48 89 e5             	mov    %rsp,%rbp
  40101f:	48 83 ec 20          	sub    $0x20,%rsp
  401023:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  401027:	89 75 e4             	mov    %esi,-0x1c(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:320
  40102a:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:322
  401031:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  401038:	eb 26                	jmp    401060 <getSpaces+0x45>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:323
  40103a:	8b 45 fc             	mov    -0x4(%rbp),%eax
  40103d:	48 63 d0             	movslq %eax,%rdx
  401040:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  401044:	48 01 d0             	add    %rdx,%rax
  401047:	0f b6 00             	movzbl (%rax),%eax
  40104a:	0f be c0             	movsbl %al,%eax
  40104d:	89 c7                	mov    %eax,%edi
  40104f:	e8 1c f5 ff ff       	callq  400570 <isspace@plt>
  401054:	85 c0                	test   %eax,%eax
  401056:	74 04                	je     40105c <getSpaces+0x41>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:324
  401058:	83 45 f8 01          	addl   $0x1,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:322
  40105c:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:322 (discriminator 1)
  401060:	8b 45 fc             	mov    -0x4(%rbp),%eax
  401063:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
  401066:	7c d2                	jl     40103a <getSpaces+0x1f>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:327
  401068:	8b 45 f8             	mov    -0x8(%rbp),%eax
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:328
  40106b:	c9                   	leaveq 
  40106c:	c3                   	retq   

000000000040106d <isCap>:
isCap():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:330
  40106d:	55                   	push   %rbp
  40106e:	48 89 e5             	mov    %rsp,%rbp
  401071:	89 f8                	mov    %edi,%eax
  401073:	88 45 fc             	mov    %al,-0x4(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:331
  401076:	80 7d fc 40          	cmpb   $0x40,-0x4(%rbp)
  40107a:	7e 0d                	jle    401089 <isCap+0x1c>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:331 (discriminator 1)
  40107c:	80 7d fc 5a          	cmpb   $0x5a,-0x4(%rbp)
  401080:	7f 07                	jg     401089 <isCap+0x1c>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:332
  401082:	b8 01 00 00 00       	mov    $0x1,%eax
  401087:	eb 05                	jmp    40108e <isCap+0x21>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:333
  401089:	b8 00 00 00 00       	mov    $0x0,%eax
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:334
  40108e:	5d                   	pop    %rbp
  40108f:	c3                   	retq   

0000000000401090 <isNum>:
isNum():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:336
  401090:	55                   	push   %rbp
  401091:	48 89 e5             	mov    %rsp,%rbp
  401094:	89 f8                	mov    %edi,%eax
  401096:	88 45 fc             	mov    %al,-0x4(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:337
  401099:	80 7d fc 2f          	cmpb   $0x2f,-0x4(%rbp)
  40109d:	7e 0d                	jle    4010ac <isNum+0x1c>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:337 (discriminator 1)
  40109f:	80 7d fc 39          	cmpb   $0x39,-0x4(%rbp)
  4010a3:	7f 07                	jg     4010ac <isNum+0x1c>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:338
  4010a5:	b8 01 00 00 00       	mov    $0x1,%eax
  4010aa:	eb 05                	jmp    4010b1 <isNum+0x21>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:339
  4010ac:	b8 00 00 00 00       	mov    $0x0,%eax
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:340
  4010b1:	5d                   	pop    %rbp
  4010b2:	c3                   	retq   

00000000004010b3 <parseStr>:
parseStr():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:342
  4010b3:	55                   	push   %rbp
  4010b4:	48 89 e5             	mov    %rsp,%rbp
  4010b7:	53                   	push   %rbx
  4010b8:	48 83 ec 48          	sub    $0x48,%rsp
  4010bc:	48 89 7d c8          	mov    %rdi,-0x38(%rbp)
  4010c0:	48 89 75 c0          	mov    %rsi,-0x40(%rbp)
  4010c4:	89 55 bc             	mov    %edx,-0x44(%rbp)
  4010c7:	89 4d b8             	mov    %ecx,-0x48(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:343
  4010ca:	c7 45 dc 00 00 00 00 	movl   $0x0,-0x24(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:344
  4010d1:	eb 04                	jmp    4010d7 <parseStr+0x24>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:345
  4010d3:	83 45 dc 01          	addl   $0x1,-0x24(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:344 (discriminator 1)
  4010d7:	8b 45 dc             	mov    -0x24(%rbp),%eax
  4010da:	48 63 d0             	movslq %eax,%rdx
  4010dd:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  4010e1:	48 01 d0             	add    %rdx,%rax
  4010e4:	0f b6 00             	movzbl (%rax),%eax
  4010e7:	0f be c0             	movsbl %al,%eax
  4010ea:	89 c7                	mov    %eax,%edi
  4010ec:	e8 7f f4 ff ff       	callq  400570 <isspace@plt>
  4010f1:	85 c0                	test   %eax,%eax
  4010f3:	75 de                	jne    4010d3 <parseStr+0x20>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:347
  4010f5:	8b 55 bc             	mov    -0x44(%rbp),%edx
  4010f8:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  4010fc:	89 d6                	mov    %edx,%esi
  4010fe:	48 89 c7             	mov    %rax,%rdi
  401101:	e8 15 ff ff ff       	callq  40101b <getSpaces>
  401106:	89 45 e4             	mov    %eax,-0x1c(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:349
  401109:	8b 45 b8             	mov    -0x48(%rbp),%eax
  40110c:	48 98                	cltq   
  40110e:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  401115:	00 
  401116:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  40111a:	48 8d 1c 02          	lea    (%rdx,%rax,1),%rbx
  40111e:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  401121:	8b 55 bc             	mov    -0x44(%rbp),%edx
  401124:	29 c2                	sub    %eax,%edx
  401126:	89 d0                	mov    %edx,%eax
  401128:	83 c0 01             	add    $0x1,%eax
  40112b:	48 98                	cltq   
  40112d:	48 89 c7             	mov    %rax,%rdi
  401130:	e8 6b f4 ff ff       	callq  4005a0 <malloc@plt>
  401135:	48 89 03             	mov    %rax,(%rbx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:350
  401138:	8b 45 b8             	mov    -0x48(%rbp),%eax
  40113b:	48 98                	cltq   
  40113d:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  401144:	00 
  401145:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  401149:	48 01 d0             	add    %rdx,%rax
  40114c:	48 8b 00             	mov    (%rax),%rax
  40114f:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:352
  401153:	e9 b5 00 00 00       	jmpq   40120d <parseStr+0x15a>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:353
  401158:	8b 45 dc             	mov    -0x24(%rbp),%eax
  40115b:	48 63 d0             	movslq %eax,%rdx
  40115e:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  401162:	48 01 d0             	add    %rdx,%rax
  401165:	0f b6 00             	movzbl (%rax),%eax
  401168:	0f be c0             	movsbl %al,%eax
  40116b:	89 c7                	mov    %eax,%edi
  40116d:	e8 fb fe ff ff       	callq  40106d <isCap>
  401172:	85 c0                	test   %eax,%eax
  401174:	74 4c                	je     4011c2 <parseStr+0x10f>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:353 (discriminator 1)
  401176:	8b 45 dc             	mov    -0x24(%rbp),%eax
  401179:	48 63 d0             	movslq %eax,%rdx
  40117c:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  401180:	48 01 d0             	add    %rdx,%rax
  401183:	0f b6 00             	movzbl (%rax),%eax
  401186:	0f be c0             	movsbl %al,%eax
  401189:	89 c7                	mov    %eax,%edi
  40118b:	e8 00 ff ff ff       	callq  401090 <isNum>
  401190:	85 c0                	test   %eax,%eax
  401192:	75 2e                	jne    4011c2 <parseStr+0x10f>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:354
  401194:	8b 45 b8             	mov    -0x48(%rbp),%eax
  401197:	48 98                	cltq   
  401199:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4011a0:	00 
  4011a1:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  4011a5:	48 01 d0             	add    %rdx,%rax
  4011a8:	48 8b 00             	mov    (%rax),%rax
  4011ab:	8b 55 dc             	mov    -0x24(%rbp),%edx
  4011ae:	48 63 ca             	movslq %edx,%rcx
  4011b1:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  4011b5:	48 01 ca             	add    %rcx,%rdx
  4011b8:	0f b6 12             	movzbl (%rdx),%edx
  4011bb:	83 c2 20             	add    $0x20,%edx
  4011be:	88 10                	mov    %dl,(%rax)
  4011c0:	eb 29                	jmp    4011eb <parseStr+0x138>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:355
  4011c2:	8b 45 b8             	mov    -0x48(%rbp),%eax
  4011c5:	48 98                	cltq   
  4011c7:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4011ce:	00 
  4011cf:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  4011d3:	48 01 d0             	add    %rdx,%rax
  4011d6:	48 8b 00             	mov    (%rax),%rax
  4011d9:	8b 55 dc             	mov    -0x24(%rbp),%edx
  4011dc:	48 63 ca             	movslq %edx,%rcx
  4011df:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  4011e3:	48 01 ca             	add    %rcx,%rdx
  4011e6:	0f b6 12             	movzbl (%rdx),%edx
  4011e9:	88 10                	mov    %dl,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:357
  4011eb:	8b 45 b8             	mov    -0x48(%rbp),%eax
  4011ee:	48 98                	cltq   
  4011f0:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4011f7:	00 
  4011f8:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  4011fc:	48 01 d0             	add    %rdx,%rax
  4011ff:	48 8b 10             	mov    (%rax),%rdx
  401202:	48 83 c2 01          	add    $0x1,%rdx
  401206:	48 89 10             	mov    %rdx,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:358
  401209:	83 45 dc 01          	addl   $0x1,-0x24(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:352 (discriminator 1)
  40120d:	8b 45 dc             	mov    -0x24(%rbp),%eax
  401210:	48 63 d0             	movslq %eax,%rdx
  401213:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  401217:	48 01 d0             	add    %rdx,%rax
  40121a:	0f b6 00             	movzbl (%rax),%eax
  40121d:	0f be c0             	movsbl %al,%eax
  401220:	89 c7                	mov    %eax,%edi
  401222:	e8 49 f3 ff ff       	callq  400570 <isspace@plt>
  401227:	85 c0                	test   %eax,%eax
  401229:	75 22                	jne    40124d <parseStr+0x19a>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:352 (discriminator 2)
  40122b:	8b 45 dc             	mov    -0x24(%rbp),%eax
  40122e:	48 63 d0             	movslq %eax,%rdx
  401231:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  401235:	48 01 d0             	add    %rdx,%rax
  401238:	0f b6 00             	movzbl (%rax),%eax
  40123b:	0f be c0             	movsbl %al,%eax
  40123e:	89 c7                	mov    %eax,%edi
  401240:	e8 1b f3 ff ff       	callq  400560 <ispunct@plt>
  401245:	85 c0                	test   %eax,%eax
  401247:	0f 84 0b ff ff ff    	je     401158 <parseStr+0xa5>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:361
  40124d:	83 45 dc 01          	addl   $0x1,-0x24(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:363
  401251:	8b 45 dc             	mov    -0x24(%rbp),%eax
  401254:	48 63 d0             	movslq %eax,%rdx
  401257:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  40125b:	48 01 d0             	add    %rdx,%rax
  40125e:	0f b6 00             	movzbl (%rax),%eax
  401261:	0f be c0             	movsbl %al,%eax
  401264:	89 c7                	mov    %eax,%edi
  401266:	e8 f5 f2 ff ff       	callq  400560 <ispunct@plt>
  40126b:	85 c0                	test   %eax,%eax
  40126d:	0f 85 64 02 00 00    	jne    4014d7 <parseStr+0x424>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:364
  401273:	c7 45 e0 01 00 00 00 	movl   $0x1,-0x20(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:365
  40127a:	e9 4c 02 00 00       	jmpq   4014cb <parseStr+0x418>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:366
  40127f:	83 7d e0 00          	cmpl   $0x0,-0x20(%rbp)
  401283:	0f 84 09 01 00 00    	je     401392 <parseStr+0x2df>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:366 (discriminator 1)
  401289:	8b 45 dc             	mov    -0x24(%rbp),%eax
  40128c:	48 63 d0             	movslq %eax,%rdx
  40128f:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  401293:	48 01 d0             	add    %rdx,%rax
  401296:	0f b6 00             	movzbl (%rax),%eax
  401299:	0f be c0             	movsbl %al,%eax
  40129c:	89 c7                	mov    %eax,%edi
  40129e:	e8 cd f2 ff ff       	callq  400570 <isspace@plt>
  4012a3:	85 c0                	test   %eax,%eax
  4012a5:	0f 85 e7 00 00 00    	jne    401392 <parseStr+0x2df>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:367
  4012ab:	8b 45 dc             	mov    -0x24(%rbp),%eax
  4012ae:	48 63 d0             	movslq %eax,%rdx
  4012b1:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  4012b5:	48 01 d0             	add    %rdx,%rax
  4012b8:	0f b6 00             	movzbl (%rax),%eax
  4012bb:	0f be c0             	movsbl %al,%eax
  4012be:	89 c7                	mov    %eax,%edi
  4012c0:	e8 a8 fd ff ff       	callq  40106d <isCap>
  4012c5:	85 c0                	test   %eax,%eax
  4012c7:	75 4c                	jne    401315 <parseStr+0x262>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:367 (discriminator 1)
  4012c9:	8b 45 dc             	mov    -0x24(%rbp),%eax
  4012cc:	48 63 d0             	movslq %eax,%rdx
  4012cf:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  4012d3:	48 01 d0             	add    %rdx,%rax
  4012d6:	0f b6 00             	movzbl (%rax),%eax
  4012d9:	0f be c0             	movsbl %al,%eax
  4012dc:	89 c7                	mov    %eax,%edi
  4012de:	e8 ad fd ff ff       	callq  401090 <isNum>
  4012e3:	85 c0                	test   %eax,%eax
  4012e5:	75 2e                	jne    401315 <parseStr+0x262>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:368
  4012e7:	8b 45 b8             	mov    -0x48(%rbp),%eax
  4012ea:	48 98                	cltq   
  4012ec:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4012f3:	00 
  4012f4:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  4012f8:	48 01 d0             	add    %rdx,%rax
  4012fb:	48 8b 00             	mov    (%rax),%rax
  4012fe:	8b 55 dc             	mov    -0x24(%rbp),%edx
  401301:	48 63 ca             	movslq %edx,%rcx
  401304:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  401308:	48 01 ca             	add    %rcx,%rdx
  40130b:	0f b6 12             	movzbl (%rdx),%edx
  40130e:	83 ea 20             	sub    $0x20,%edx
  401311:	88 10                	mov    %dl,(%rax)
  401313:	eb 29                	jmp    40133e <parseStr+0x28b>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:369
  401315:	8b 45 b8             	mov    -0x48(%rbp),%eax
  401318:	48 98                	cltq   
  40131a:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  401321:	00 
  401322:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  401326:	48 01 d0             	add    %rdx,%rax
  401329:	48 8b 00             	mov    (%rax),%rax
  40132c:	8b 55 dc             	mov    -0x24(%rbp),%edx
  40132f:	48 63 ca             	movslq %edx,%rcx
  401332:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  401336:	48 01 ca             	add    %rcx,%rdx
  401339:	0f b6 12             	movzbl (%rdx),%edx
  40133c:	88 10                	mov    %dl,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:371
  40133e:	8b 45 b8             	mov    -0x48(%rbp),%eax
  401341:	48 98                	cltq   
  401343:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  40134a:	00 
  40134b:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  40134f:	48 01 d0             	add    %rdx,%rax
  401352:	48 8b 10             	mov    (%rax),%rdx
  401355:	48 83 c2 01          	add    $0x1,%rdx
  401359:	48 89 10             	mov    %rdx,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:372
  40135c:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:374
  401363:	8b 45 dc             	mov    -0x24(%rbp),%eax
  401366:	48 63 d0             	movslq %eax,%rdx
  401369:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  40136d:	48 01 d0             	add    %rdx,%rax
  401370:	0f b6 00             	movzbl (%rax),%eax
  401373:	0f be c0             	movsbl %al,%eax
  401376:	89 c7                	mov    %eax,%edi
  401378:	e8 13 fd ff ff       	callq  401090 <isNum>
  40137d:	85 c0                	test   %eax,%eax
  40137f:	74 0c                	je     40138d <parseStr+0x2da>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:375
  401381:	c7 45 e0 01 00 00 00 	movl   $0x1,-0x20(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:374
  401388:	e9 3a 01 00 00       	jmpq   4014c7 <parseStr+0x414>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:374 (discriminator 1)
  40138d:	e9 35 01 00 00       	jmpq   4014c7 <parseStr+0x414>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:377
  401392:	8b 45 dc             	mov    -0x24(%rbp),%eax
  401395:	48 63 d0             	movslq %eax,%rdx
  401398:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  40139c:	48 01 d0             	add    %rdx,%rax
  40139f:	0f b6 00             	movzbl (%rax),%eax
  4013a2:	0f be c0             	movsbl %al,%eax
  4013a5:	89 c7                	mov    %eax,%edi
  4013a7:	e8 c1 fc ff ff       	callq  40106d <isCap>
  4013ac:	85 c0                	test   %eax,%eax
  4013ae:	74 6d                	je     40141d <parseStr+0x36a>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:377 (discriminator 1)
  4013b0:	8b 45 dc             	mov    -0x24(%rbp),%eax
  4013b3:	48 63 d0             	movslq %eax,%rdx
  4013b6:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  4013ba:	48 01 d0             	add    %rdx,%rax
  4013bd:	0f b6 00             	movzbl (%rax),%eax
  4013c0:	0f be c0             	movsbl %al,%eax
  4013c3:	89 c7                	mov    %eax,%edi
  4013c5:	e8 a6 f1 ff ff       	callq  400570 <isspace@plt>
  4013ca:	85 c0                	test   %eax,%eax
  4013cc:	75 4f                	jne    40141d <parseStr+0x36a>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:378
  4013ce:	8b 45 b8             	mov    -0x48(%rbp),%eax
  4013d1:	48 98                	cltq   
  4013d3:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4013da:	00 
  4013db:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  4013df:	48 01 d0             	add    %rdx,%rax
  4013e2:	48 8b 00             	mov    (%rax),%rax
  4013e5:	8b 55 dc             	mov    -0x24(%rbp),%edx
  4013e8:	48 63 ca             	movslq %edx,%rcx
  4013eb:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  4013ef:	48 01 ca             	add    %rcx,%rdx
  4013f2:	0f b6 12             	movzbl (%rdx),%edx
  4013f5:	83 c2 20             	add    $0x20,%edx
  4013f8:	88 10                	mov    %dl,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:379
  4013fa:	8b 45 b8             	mov    -0x48(%rbp),%eax
  4013fd:	48 98                	cltq   
  4013ff:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  401406:	00 
  401407:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  40140b:	48 01 d0             	add    %rdx,%rax
  40140e:	48 8b 10             	mov    (%rax),%rdx
  401411:	48 83 c2 01          	add    $0x1,%rdx
  401415:	48 89 10             	mov    %rdx,(%rax)
  401418:	e9 aa 00 00 00       	jmpq   4014c7 <parseStr+0x414>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:381
  40141d:	8b 45 dc             	mov    -0x24(%rbp),%eax
  401420:	48 63 d0             	movslq %eax,%rdx
  401423:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  401427:	48 01 d0             	add    %rdx,%rax
  40142a:	0f b6 00             	movzbl (%rax),%eax
  40142d:	0f be c0             	movsbl %al,%eax
  401430:	89 c7                	mov    %eax,%edi
  401432:	e8 36 fc ff ff       	callq  40106d <isCap>
  401437:	85 c0                	test   %eax,%eax
  401439:	75 67                	jne    4014a2 <parseStr+0x3ef>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:381 (discriminator 1)
  40143b:	8b 45 dc             	mov    -0x24(%rbp),%eax
  40143e:	48 63 d0             	movslq %eax,%rdx
  401441:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  401445:	48 01 d0             	add    %rdx,%rax
  401448:	0f b6 00             	movzbl (%rax),%eax
  40144b:	0f be c0             	movsbl %al,%eax
  40144e:	89 c7                	mov    %eax,%edi
  401450:	e8 1b f1 ff ff       	callq  400570 <isspace@plt>
  401455:	85 c0                	test   %eax,%eax
  401457:	75 49                	jne    4014a2 <parseStr+0x3ef>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:382
  401459:	8b 45 b8             	mov    -0x48(%rbp),%eax
  40145c:	48 98                	cltq   
  40145e:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  401465:	00 
  401466:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  40146a:	48 01 d0             	add    %rdx,%rax
  40146d:	48 8b 00             	mov    (%rax),%rax
  401470:	8b 55 dc             	mov    -0x24(%rbp),%edx
  401473:	48 63 ca             	movslq %edx,%rcx
  401476:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  40147a:	48 01 ca             	add    %rcx,%rdx
  40147d:	0f b6 12             	movzbl (%rdx),%edx
  401480:	88 10                	mov    %dl,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:383
  401482:	8b 45 b8             	mov    -0x48(%rbp),%eax
  401485:	48 98                	cltq   
  401487:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  40148e:	00 
  40148f:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  401493:	48 01 d0             	add    %rdx,%rax
  401496:	48 8b 10             	mov    (%rax),%rdx
  401499:	48 83 c2 01          	add    $0x1,%rdx
  40149d:	48 89 10             	mov    %rdx,(%rax)
  4014a0:	eb 25                	jmp    4014c7 <parseStr+0x414>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:385
  4014a2:	8b 45 dc             	mov    -0x24(%rbp),%eax
  4014a5:	48 63 d0             	movslq %eax,%rdx
  4014a8:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  4014ac:	48 01 d0             	add    %rdx,%rax
  4014af:	0f b6 00             	movzbl (%rax),%eax
  4014b2:	0f be c0             	movsbl %al,%eax
  4014b5:	89 c7                	mov    %eax,%edi
  4014b7:	e8 b4 f0 ff ff       	callq  400570 <isspace@plt>
  4014bc:	85 c0                	test   %eax,%eax
  4014be:	74 07                	je     4014c7 <parseStr+0x414>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:386
  4014c0:	c7 45 e0 01 00 00 00 	movl   $0x1,-0x20(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:365
  4014c7:	83 45 dc 01          	addl   $0x1,-0x24(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:365 (discriminator 1)
  4014cb:	8b 45 dc             	mov    -0x24(%rbp),%eax
  4014ce:	3b 45 bc             	cmp    -0x44(%rbp),%eax
  4014d1:	0f 8c a8 fd ff ff    	jl     40127f <parseStr+0x1cc>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:391
  4014d7:	8b 45 b8             	mov    -0x48(%rbp),%eax
  4014da:	48 98                	cltq   
  4014dc:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4014e3:	00 
  4014e4:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  4014e8:	48 01 d0             	add    %rdx,%rax
  4014eb:	48 8b 00             	mov    (%rax),%rax
  4014ee:	c6 00 00             	movb   $0x0,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:392
  4014f1:	8b 45 b8             	mov    -0x48(%rbp),%eax
  4014f4:	48 98                	cltq   
  4014f6:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4014fd:	00 
  4014fe:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  401502:	48 01 c2             	add    %rax,%rdx
  401505:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  401509:	48 89 02             	mov    %rax,(%rdx)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:393
  40150c:	48 83 c4 48          	add    $0x48,%rsp
  401510:	5b                   	pop    %rbx
  401511:	5d                   	pop    %rbp
  401512:	c3                   	retq   

0000000000401513 <getSentences>:
getSentences():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:395
  401513:	55                   	push   %rbp
  401514:	48 89 e5             	mov    %rsp,%rbp
  401517:	48 83 ec 30          	sub    $0x30,%rsp
  40151b:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
  40151f:	48 89 75 d0          	mov    %rsi,-0x30(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:396
  401523:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  401527:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:397
  40152b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  40152f:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:399
  401533:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  401537:	48 89 c7             	mov    %rax,%rdi
  40153a:	e8 11 f0 ff ff       	callq  400550 <strlen@plt>
  40153f:	89 45 ec             	mov    %eax,-0x14(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:400
  401542:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:401
  401549:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:403
  401550:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%rbp)
  401557:	eb 5d                	jmp    4015b6 <getSentences+0xa3>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:404
  401559:	48 83 45 f0 01       	addq   $0x1,-0x10(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:406
  40155e:	8b 45 e8             	mov    -0x18(%rbp),%eax
  401561:	48 63 d0             	movslq %eax,%rdx
  401564:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  401568:	48 01 d0             	add    %rdx,%rax
  40156b:	0f b6 00             	movzbl (%rax),%eax
  40156e:	0f be c0             	movsbl %al,%eax
  401571:	89 c7                	mov    %eax,%edi
  401573:	e8 e8 ef ff ff       	callq  400560 <ispunct@plt>
  401578:	85 c0                	test   %eax,%eax
  40157a:	74 36                	je     4015b2 <getSentences+0x9f>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:407
  40157c:	8b 45 e0             	mov    -0x20(%rbp),%eax
  40157f:	8b 55 e8             	mov    -0x18(%rbp),%edx
  401582:	89 d7                	mov    %edx,%edi
  401584:	29 c7                	sub    %eax,%edi
  401586:	8b 55 e4             	mov    -0x1c(%rbp),%edx
  401589:	48 8b 75 d0          	mov    -0x30(%rbp),%rsi
  40158d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401591:	89 d1                	mov    %edx,%ecx
  401593:	89 fa                	mov    %edi,%edx
  401595:	48 89 c7             	mov    %rax,%rdi
  401598:	e8 16 fb ff ff       	callq  4010b3 <parseStr>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:408
  40159d:	8b 45 e8             	mov    -0x18(%rbp),%eax
  4015a0:	83 c0 01             	add    $0x1,%eax
  4015a3:	89 45 e0             	mov    %eax,-0x20(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:409
  4015a6:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4015aa:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:410
  4015ae:	83 45 e4 01          	addl   $0x1,-0x1c(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:403
  4015b2:	83 45 e8 01          	addl   $0x1,-0x18(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:403 (discriminator 1)
  4015b6:	8b 45 e8             	mov    -0x18(%rbp),%eax
  4015b9:	3b 45 ec             	cmp    -0x14(%rbp),%eax
  4015bc:	7c 9b                	jl     401559 <getSentences+0x46>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:414
  4015be:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  4015c1:	48 98                	cltq   
  4015c3:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4015ca:	00 
  4015cb:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  4015cf:	48 01 d0             	add    %rdx,%rax
  4015d2:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:415
  4015d9:	c9                   	leaveq 
  4015da:	c3                   	retq   

00000000004015db <camel_caser>:
camel_caser():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:417
  4015db:	55                   	push   %rbp
  4015dc:	48 89 e5             	mov    %rsp,%rbp
  4015df:	48 83 ec 20          	sub    $0x20,%rsp
  4015e3:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:418
  4015e7:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  4015ec:	75 07                	jne    4015f5 <camel_caser+0x1a>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:419
  4015ee:	b8 00 00 00 00       	mov    $0x0,%eax
  4015f3:	eb 3e                	jmp    401633 <camel_caser+0x58>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:421
  4015f5:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  4015f9:	48 89 c7             	mov    %rax,%rdi
  4015fc:	e8 bc f9 ff ff       	callq  400fbd <findPunct>
  401601:	89 45 f4             	mov    %eax,-0xc(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:423
  401604:	8b 45 f4             	mov    -0xc(%rbp),%eax
  401607:	83 c0 01             	add    $0x1,%eax
  40160a:	48 98                	cltq   
  40160c:	48 c1 e0 03          	shl    $0x3,%rax
  401610:	48 89 c7             	mov    %rax,%rdi
  401613:	e8 88 ef ff ff       	callq  4005a0 <malloc@plt>
  401618:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:425
  40161c:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
  401620:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  401624:	48 89 d6             	mov    %rdx,%rsi
  401627:	48 89 c7             	mov    %rax,%rdi
  40162a:	e8 e4 fe ff ff       	callq  401513 <getSentences>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:427
  40162f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:428
  401633:	c9                   	leaveq 
  401634:	c3                   	retq   

0000000000401635 <main>:
main():
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:430
  401635:	55                   	push   %rbp
  401636:	48 89 e5             	mov    %rsp,%rbp
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:431
  401639:	bf db 15 40 00       	mov    $0x4015db,%edi
  40163e:	e8 ba f1 ff ff       	callq  4007fd <test_camelCaser>
  401643:	85 c0                	test   %eax,%eax
  401645:	74 0c                	je     401653 <main+0x1e>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:432
  401647:	bf 68 1f 40 00       	mov    $0x401f68,%edi
  40164c:	e8 ef ee ff ff       	callq  400540 <puts@plt>
  401651:	eb 0a                	jmp    40165d <main+0x28>
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:433
  401653:	bf 70 1f 40 00       	mov    $0x401f70,%edi
  401658:	e8 e3 ee ff ff       	callq  400540 <puts@plt>
  40165d:	b8 00 00 00 00       	mov    $0x0,%eax
/home/guiping/cs241/honorsProjekt/testCamel_sol.c:434
  401662:	5d                   	pop    %rbp
  401663:	c3                   	retq   
  401664:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40166b:	00 00 00 
  40166e:	66 90                	xchg   %ax,%ax

0000000000401670 <__libc_csu_init>:
__libc_csu_init():
  401670:	41 57                	push   %r15
  401672:	41 89 ff             	mov    %edi,%r15d
  401675:	41 56                	push   %r14
  401677:	49 89 f6             	mov    %rsi,%r14
  40167a:	41 55                	push   %r13
  40167c:	49 89 d5             	mov    %rdx,%r13
  40167f:	41 54                	push   %r12
  401681:	4c 8d 25 88 17 20 00 	lea    0x201788(%rip),%r12        # 602e10 <__frame_dummy_init_array_entry>
  401688:	55                   	push   %rbp
  401689:	48 8d 2d 88 17 20 00 	lea    0x201788(%rip),%rbp        # 602e18 <__init_array_end>
  401690:	53                   	push   %rbx
  401691:	4c 29 e5             	sub    %r12,%rbp
  401694:	31 db                	xor    %ebx,%ebx
  401696:	48 c1 fd 03          	sar    $0x3,%rbp
  40169a:	48 83 ec 08          	sub    $0x8,%rsp
  40169e:	e8 5d ee ff ff       	callq  400500 <_init>
  4016a3:	48 85 ed             	test   %rbp,%rbp
  4016a6:	74 1e                	je     4016c6 <__libc_csu_init+0x56>
  4016a8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4016af:	00 
  4016b0:	4c 89 ea             	mov    %r13,%rdx
  4016b3:	4c 89 f6             	mov    %r14,%rsi
  4016b6:	44 89 ff             	mov    %r15d,%edi
  4016b9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4016bd:	48 83 c3 01          	add    $0x1,%rbx
  4016c1:	48 39 eb             	cmp    %rbp,%rbx
  4016c4:	75 ea                	jne    4016b0 <__libc_csu_init+0x40>
  4016c6:	48 83 c4 08          	add    $0x8,%rsp
  4016ca:	5b                   	pop    %rbx
  4016cb:	5d                   	pop    %rbp
  4016cc:	41 5c                	pop    %r12
  4016ce:	41 5d                	pop    %r13
  4016d0:	41 5e                	pop    %r14
  4016d2:	41 5f                	pop    %r15
  4016d4:	c3                   	retq   
  4016d5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  4016dc:	00 00 00 00 

00000000004016e0 <__libc_csu_fini>:
__libc_csu_fini():
  4016e0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004016e4 <_fini>:
_fini():
  4016e4:	48 83 ec 08          	sub    $0x8,%rsp
  4016e8:	48 83 c4 08          	add    $0x8,%rsp
  4016ec:	c3                   	retq   
