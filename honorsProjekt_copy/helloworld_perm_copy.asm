
./helloworld:     file format elf64-x86-64


Disassembly of section .init:

00000000004006b0 <_init>:
_init():
  4006b0:	48 83 ec 08          	sub    $0x8,%rsp
  4006b4:	48 8b 05 3d 09 20 00 	mov    0x20093d(%rip),%rax        # 600ff8 <_DYNAMIC+0x1e0>
  4006bb:	48 85 c0             	test   %rax,%rax
  4006be:	74 05                	je     4006c5 <_init+0x15>
  4006c0:	e8 2b 00 00 00       	callq  4006f0 <__gmon_start__@plt>
  4006c5:	48 83 c4 08          	add    $0x8,%rsp
  4006c9:	c3                   	retq   

Disassembly of section .plt:

00000000004006d0 <_ZNSolsEi@plt-0x10>:
  4006d0:	ff 35 32 09 20 00    	pushq  0x200932(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  4006d6:	ff 25 34 09 20 00    	jmpq   *0x200934(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  4006dc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004006e0 <_ZNSolsEi@plt>:
  4006e0:	ff 25 32 09 20 00    	jmpq   *0x200932(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  4006e6:	68 00 00 00 00       	pushq  $0x0
  4006eb:	e9 e0 ff ff ff       	jmpq   4006d0 <_init+0x20>

00000000004006f0 <__gmon_start__@plt>:
  4006f0:	ff 25 2a 09 20 00    	jmpq   *0x20092a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  4006f6:	68 01 00 00 00       	pushq  $0x1
  4006fb:	e9 d0 ff ff ff       	jmpq   4006d0 <_init+0x20>

0000000000400700 <_ZNSt8ios_base4InitC1Ev@plt>:
  400700:	ff 25 22 09 20 00    	jmpq   *0x200922(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  400706:	68 02 00 00 00       	pushq  $0x2
  40070b:	e9 c0 ff ff ff       	jmpq   4006d0 <_init+0x20>

0000000000400710 <__libc_start_main@plt>:
  400710:	ff 25 1a 09 20 00    	jmpq   *0x20091a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  400716:	68 03 00 00 00       	pushq  $0x3
  40071b:	e9 b0 ff ff ff       	jmpq   4006d0 <_init+0x20>

0000000000400720 <__cxa_atexit@plt>:
  400720:	ff 25 12 09 20 00    	jmpq   *0x200912(%rip)        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  400726:	68 04 00 00 00       	pushq  $0x4
  40072b:	e9 a0 ff ff ff       	jmpq   4006d0 <_init+0x20>

0000000000400730 <_ZNSt8ios_base4InitD1Ev@plt>:
  400730:	ff 25 0a 09 20 00    	jmpq   *0x20090a(%rip)        # 601040 <_GLOBAL_OFFSET_TABLE_+0x40>
  400736:	68 05 00 00 00       	pushq  $0x5
  40073b:	e9 90 ff ff ff       	jmpq   4006d0 <_init+0x20>

0000000000400740 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>:
  400740:	ff 25 02 09 20 00    	jmpq   *0x200902(%rip)        # 601048 <_GLOBAL_OFFSET_TABLE_+0x48>
  400746:	68 06 00 00 00       	pushq  $0x6
  40074b:	e9 80 ff ff ff       	jmpq   4006d0 <_init+0x20>

Disassembly of section .text:

0000000000400750 <_start>:
_start():
  400750:	31 ed                	xor    %ebp,%ebp
  400752:	49 89 d1             	mov    %rdx,%r9
  400755:	5e                   	pop    %rsi
  400756:	48 89 e2             	mov    %rsp,%rdx
  400759:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40075d:	50                   	push   %rax
  40075e:	54                   	push   %rsp
  40075f:	49 c7 c0 c0 09 40 00 	mov    $0x4009c0,%r8
  400766:	48 c7 c1 50 09 40 00 	mov    $0x400950,%rcx
  40076d:	48 c7 c7 3d 08 40 00 	mov    $0x40083d,%rdi
  400774:	e8 97 ff ff ff       	callq  400710 <__libc_start_main@plt>
  400779:	f4                   	hlt    
  40077a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400780 <deregister_tm_clones>:
deregister_tm_clones():
  400780:	b8 67 10 60 00       	mov    $0x601067,%eax
  400785:	55                   	push   %rbp
  400786:	48 2d 60 10 60 00    	sub    $0x601060,%rax
  40078c:	48 83 f8 0e          	cmp    $0xe,%rax
  400790:	48 89 e5             	mov    %rsp,%rbp
  400793:	77 02                	ja     400797 <deregister_tm_clones+0x17>
  400795:	5d                   	pop    %rbp
  400796:	c3                   	retq   
  400797:	b8 00 00 00 00       	mov    $0x0,%eax
  40079c:	48 85 c0             	test   %rax,%rax
  40079f:	74 f4                	je     400795 <deregister_tm_clones+0x15>
  4007a1:	5d                   	pop    %rbp
  4007a2:	bf 60 10 60 00       	mov    $0x601060,%edi
  4007a7:	ff e0                	jmpq   *%rax
  4007a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004007b0 <register_tm_clones>:
register_tm_clones():
  4007b0:	b8 60 10 60 00       	mov    $0x601060,%eax
  4007b5:	55                   	push   %rbp
  4007b6:	48 2d 60 10 60 00    	sub    $0x601060,%rax
  4007bc:	48 c1 f8 03          	sar    $0x3,%rax
  4007c0:	48 89 e5             	mov    %rsp,%rbp
  4007c3:	48 89 c2             	mov    %rax,%rdx
  4007c6:	48 c1 ea 3f          	shr    $0x3f,%rdx
  4007ca:	48 01 d0             	add    %rdx,%rax
  4007cd:	48 d1 f8             	sar    %rax
  4007d0:	75 02                	jne    4007d4 <register_tm_clones+0x24>
  4007d2:	5d                   	pop    %rbp
  4007d3:	c3                   	retq   
  4007d4:	ba 00 00 00 00       	mov    $0x0,%edx
  4007d9:	48 85 d2             	test   %rdx,%rdx
  4007dc:	74 f4                	je     4007d2 <register_tm_clones+0x22>
  4007de:	5d                   	pop    %rbp
  4007df:	48 89 c6             	mov    %rax,%rsi
  4007e2:	bf 60 10 60 00       	mov    $0x601060,%edi
  4007e7:	ff e2                	jmpq   *%rdx
  4007e9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004007f0 <__do_global_dtors_aux>:
__do_global_dtors_aux():
  4007f0:	80 3d 99 0a 20 00 00 	cmpb   $0x0,0x200a99(%rip)        # 601290 <completed.6973>
  4007f7:	75 11                	jne    40080a <__do_global_dtors_aux+0x1a>
  4007f9:	55                   	push   %rbp
  4007fa:	48 89 e5             	mov    %rsp,%rbp
  4007fd:	e8 7e ff ff ff       	callq  400780 <deregister_tm_clones>
  400802:	5d                   	pop    %rbp
  400803:	c6 05 86 0a 20 00 01 	movb   $0x1,0x200a86(%rip)        # 601290 <completed.6973>
  40080a:	f3 c3                	repz retq 
  40080c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400810 <frame_dummy>:
frame_dummy():
  400810:	48 83 3d f8 05 20 00 	cmpq   $0x0,0x2005f8(%rip)        # 600e10 <__JCR_END__>
  400817:	00 
  400818:	74 1e                	je     400838 <frame_dummy+0x28>
  40081a:	b8 00 00 00 00       	mov    $0x0,%eax
  40081f:	48 85 c0             	test   %rax,%rax
  400822:	74 14                	je     400838 <frame_dummy+0x28>
  400824:	55                   	push   %rbp
  400825:	bf 10 0e 60 00       	mov    $0x600e10,%edi
  40082a:	48 89 e5             	mov    %rsp,%rbp
  40082d:	ff d0                	callq  *%rax
  40082f:	5d                   	pop    %rbp
  400830:	e9 7b ff ff ff       	jmpq   4007b0 <register_tm_clones>
  400835:	0f 1f 00             	nopl   (%rax)
  400838:	e9 73 ff ff ff       	jmpq   4007b0 <register_tm_clones>

000000000040083d <main>:
main():
/home/guiping/cs241/honorsProjekt/helloworld.cpp:24
  40083d:	55                   	push   %rbp
  40083e:	48 89 e5             	mov    %rsp,%rbp
  400841:	48 83 ec 10          	sub    $0x10,%rsp
/home/guiping/cs241/honorsProjekt/helloworld.cpp:53
  400845:	be e0 09 40 00       	mov    $0x4009e0,%esi
  40084a:	bf 80 11 60 00       	mov    $0x601180,%edi
  40084f:	e8 ec fe ff ff       	callq  400740 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:54
  400854:	be 02 0a 40 00       	mov    $0x400a02,%esi
  400859:	bf 80 11 60 00       	mov    $0x601180,%edi
  40085e:	e8 dd fe ff ff       	callq  400740 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:57
  400863:	be 20 0a 40 00       	mov    $0x400a20,%esi
  400868:	bf 80 11 60 00       	mov    $0x601180,%edi
  40086d:	e8 ce fe ff ff       	callq  400740 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:58
  400872:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:59
  400879:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  400880:	eb 0a                	jmp    40088c <main+0x4f>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:60 (discriminator 2)
  400882:	8b 45 fc             	mov    -0x4(%rbp),%eax
  400885:	01 45 f8             	add    %eax,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:59 (discriminator 2)
  400888:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:59 (discriminator 1)
  40088c:	83 7d fc 09          	cmpl   $0x9,-0x4(%rbp)
  400890:	7e f0                	jle    400882 <main+0x45>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:62
  400892:	be 5d 0a 40 00       	mov    $0x400a5d,%esi
  400897:	bf 80 11 60 00       	mov    $0x601180,%edi
  40089c:	e8 9f fe ff ff       	callq  400740 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
  4008a1:	8b 55 f8             	mov    -0x8(%rbp),%edx
  4008a4:	89 d6                	mov    %edx,%esi
  4008a6:	48 89 c7             	mov    %rax,%rdi
  4008a9:	e8 32 fe ff ff       	callq  4006e0 <_ZNSolsEi@plt>
  4008ae:	be 6a 0a 40 00       	mov    $0x400a6a,%esi
  4008b3:	48 89 c7             	mov    %rax,%rdi
  4008b6:	e8 85 fe ff ff       	callq  400740 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:64
  4008bb:	be 70 0a 40 00       	mov    $0x400a70,%esi
  4008c0:	bf 80 11 60 00       	mov    $0x601180,%edi
  4008c5:	e8 76 fe ff ff       	callq  400740 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:66
  4008ca:	be 98 0a 40 00       	mov    $0x400a98,%esi
  4008cf:	bf 80 11 60 00       	mov    $0x601180,%edi
  4008d4:	e8 67 fe ff ff       	callq  400740 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:68
  4008d9:	be cb 0a 40 00       	mov    $0x400acb,%esi
  4008de:	bf 60 10 60 00       	mov    $0x601060,%edi
  4008e3:	e8 58 fe ff ff       	callq  400740 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:81
  4008e8:	b8 00 00 00 00       	mov    $0x0,%eax
/home/guiping/cs241/honorsProjekt/helloworld.cpp:82
  4008ed:	c9                   	leaveq 
  4008ee:	c3                   	retq   

00000000004008ef <_Z41__static_initialization_and_destruction_0ii>:
__static_initialization_and_destruction_0():
  4008ef:	55                   	push   %rbp
  4008f0:	48 89 e5             	mov    %rsp,%rbp
  4008f3:	48 83 ec 10          	sub    $0x10,%rsp
  4008f7:	89 7d fc             	mov    %edi,-0x4(%rbp)
  4008fa:	89 75 f8             	mov    %esi,-0x8(%rbp)
  4008fd:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
  400901:	75 27                	jne    40092a <_Z41__static_initialization_and_destruction_0ii+0x3b>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:82 (discriminator 1)
  400903:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
  40090a:	75 1e                	jne    40092a <_Z41__static_initialization_and_destruction_0ii+0x3b>
/usr/include/c++/4.8/iostream:74
  40090c:	bf 91 12 60 00       	mov    $0x601291,%edi
  400911:	e8 ea fd ff ff       	callq  400700 <_ZNSt8ios_base4InitC1Ev@plt>
  400916:	ba 58 10 60 00       	mov    $0x601058,%edx
  40091b:	be 91 12 60 00       	mov    $0x601291,%esi
  400920:	bf 30 07 40 00       	mov    $0x400730,%edi
  400925:	e8 f6 fd ff ff       	callq  400720 <__cxa_atexit@plt>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:82
  40092a:	c9                   	leaveq 
  40092b:	c3                   	retq   

000000000040092c <_GLOBAL__sub_I_main>:
_GLOBAL__sub_I_main():
  40092c:	55                   	push   %rbp
  40092d:	48 89 e5             	mov    %rsp,%rbp
  400930:	be ff ff 00 00       	mov    $0xffff,%esi
  400935:	bf 01 00 00 00       	mov    $0x1,%edi
  40093a:	e8 b0 ff ff ff       	callq  4008ef <_Z41__static_initialization_and_destruction_0ii>
  40093f:	5d                   	pop    %rbp
  400940:	c3                   	retq   
  400941:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400948:	00 00 00 
  40094b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400950 <__libc_csu_init>:
__libc_csu_init():
  400950:	41 57                	push   %r15
  400952:	41 89 ff             	mov    %edi,%r15d
  400955:	41 56                	push   %r14
  400957:	49 89 f6             	mov    %rsi,%r14
  40095a:	41 55                	push   %r13
  40095c:	49 89 d5             	mov    %rdx,%r13
  40095f:	41 54                	push   %r12
  400961:	4c 8d 25 90 04 20 00 	lea    0x200490(%rip),%r12        # 600df8 <__frame_dummy_init_array_entry>
  400968:	55                   	push   %rbp
  400969:	48 8d 2d 98 04 20 00 	lea    0x200498(%rip),%rbp        # 600e08 <__init_array_end>
  400970:	53                   	push   %rbx
  400971:	4c 29 e5             	sub    %r12,%rbp
  400974:	31 db                	xor    %ebx,%ebx
  400976:	48 c1 fd 03          	sar    $0x3,%rbp
  40097a:	48 83 ec 08          	sub    $0x8,%rsp
  40097e:	e8 2d fd ff ff       	callq  4006b0 <_init>
  400983:	48 85 ed             	test   %rbp,%rbp
  400986:	74 1e                	je     4009a6 <__libc_csu_init+0x56>
  400988:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40098f:	00 
  400990:	4c 89 ea             	mov    %r13,%rdx
  400993:	4c 89 f6             	mov    %r14,%rsi
  400996:	44 89 ff             	mov    %r15d,%edi
  400999:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40099d:	48 83 c3 01          	add    $0x1,%rbx
  4009a1:	48 39 eb             	cmp    %rbp,%rbx
  4009a4:	75 ea                	jne    400990 <__libc_csu_init+0x40>
  4009a6:	48 83 c4 08          	add    $0x8,%rsp
  4009aa:	5b                   	pop    %rbx
  4009ab:	5d                   	pop    %rbp
  4009ac:	41 5c                	pop    %r12
  4009ae:	41 5d                	pop    %r13
  4009b0:	41 5e                	pop    %r14
  4009b2:	41 5f                	pop    %r15
  4009b4:	c3                   	retq   
  4009b5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  4009bc:	00 00 00 00 

00000000004009c0 <__libc_csu_fini>:
__libc_csu_fini():
  4009c0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004009c4 <_fini>:
_fini():
  4009c4:	48 83 ec 08          	sub    $0x8,%rsp
  4009c8:	48 83 c4 08          	add    $0x8,%rsp
  4009cc:	c3                   	retq   
00a61:	48 39 eb             	cmp    %rbp,%rbx
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
