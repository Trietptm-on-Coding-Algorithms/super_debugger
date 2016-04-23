
./a.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000400558 <_init>:
_init():
  400558:	48 83 ec 08          	sub    $0x8,%rsp
  40055c:	48 8b 05 95 0a 20 00 	mov    0x200a95(%rip),%rax        # 600ff8 <_DYNAMIC+0x1e0>
  400563:	48 85 c0             	test   %rax,%rax
  400566:	74 05                	je     40056d <_init+0x15>
  400568:	e8 23 00 00 00       	callq  400590 <__gmon_start__@plt>
  40056d:	48 83 c4 08          	add    $0x8,%rsp
  400571:	c3                   	retq   

Disassembly of section .plt:

0000000000400580 <__gmon_start__@plt-0x10>:
  400580:	ff 35 82 0a 20 00    	pushq  0x200a82(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400586:	ff 25 84 0a 20 00    	jmpq   *0x200a84(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40058c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400590 <__gmon_start__@plt>:
  400590:	ff 25 82 0a 20 00    	jmpq   *0x200a82(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400596:	68 00 00 00 00       	pushq  $0x0
  40059b:	e9 e0 ff ff ff       	jmpq   400580 <_init+0x28>

00000000004005a0 <_ZNSt8ios_base4InitC1Ev@plt>:
  4005a0:	ff 25 7a 0a 20 00    	jmpq   *0x200a7a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  4005a6:	68 01 00 00 00       	pushq  $0x1
  4005ab:	e9 d0 ff ff ff       	jmpq   400580 <_init+0x28>

00000000004005b0 <__libc_start_main@plt>:
  4005b0:	ff 25 72 0a 20 00    	jmpq   *0x200a72(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  4005b6:	68 02 00 00 00       	pushq  $0x2
  4005bb:	e9 c0 ff ff ff       	jmpq   400580 <_init+0x28>

00000000004005c0 <__cxa_atexit@plt>:
  4005c0:	ff 25 6a 0a 20 00    	jmpq   *0x200a6a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  4005c6:	68 03 00 00 00       	pushq  $0x3
  4005cb:	e9 b0 ff ff ff       	jmpq   400580 <_init+0x28>

00000000004005d0 <_ZNSt8ios_base4InitD1Ev@plt>:
  4005d0:	ff 25 62 0a 20 00    	jmpq   *0x200a62(%rip)        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  4005d6:	68 04 00 00 00       	pushq  $0x4
  4005db:	e9 a0 ff ff ff       	jmpq   400580 <_init+0x28>

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
  4005ef:	49 c7 c0 c0 07 40 00 	mov    $0x4007c0,%r8
  4005f6:	48 c7 c1 50 07 40 00 	mov    $0x400750,%rcx
  4005fd:	48 c7 c7 cd 06 40 00 	mov    $0x4006cd,%rdi
  400604:	e8 a7 ff ff ff       	callq  4005b0 <__libc_start_main@plt>
  400609:	f4                   	hlt    
  40060a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400610 <deregister_tm_clones>:
deregister_tm_clones():
  400610:	b8 57 10 60 00       	mov    $0x601057,%eax
  400615:	55                   	push   %rbp
  400616:	48 2d 50 10 60 00    	sub    $0x601050,%rax
  40061c:	48 83 f8 0e          	cmp    $0xe,%rax
  400620:	48 89 e5             	mov    %rsp,%rbp
  400623:	77 02                	ja     400627 <deregister_tm_clones+0x17>
  400625:	5d                   	pop    %rbp
  400626:	c3                   	retq   
  400627:	b8 00 00 00 00       	mov    $0x0,%eax
  40062c:	48 85 c0             	test   %rax,%rax
  40062f:	74 f4                	je     400625 <deregister_tm_clones+0x15>
  400631:	5d                   	pop    %rbp
  400632:	bf 50 10 60 00       	mov    $0x601050,%edi
  400637:	ff e0                	jmpq   *%rax
  400639:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400640 <register_tm_clones>:
register_tm_clones():
  400640:	b8 50 10 60 00       	mov    $0x601050,%eax
  400645:	55                   	push   %rbp
  400646:	48 2d 50 10 60 00    	sub    $0x601050,%rax
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
  400672:	bf 50 10 60 00       	mov    $0x601050,%edi
  400677:	ff e2                	jmpq   *%rdx
  400679:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400680 <__do_global_dtors_aux>:
__do_global_dtors_aux():
  400680:	80 3d c9 09 20 00 00 	cmpb   $0x0,0x2009c9(%rip)        # 601050 <__TMC_END__>
  400687:	75 11                	jne    40069a <__do_global_dtors_aux+0x1a>
  400689:	55                   	push   %rbp
  40068a:	48 89 e5             	mov    %rsp,%rbp
  40068d:	e8 7e ff ff ff       	callq  400610 <deregister_tm_clones>
  400692:	5d                   	pop    %rbp
  400693:	c6 05 b6 09 20 00 01 	movb   $0x1,0x2009b6(%rip)        # 601050 <__TMC_END__>
  40069a:	f3 c3                	repz retq 
  40069c:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004006a0 <frame_dummy>:
frame_dummy():
  4006a0:	48 83 3d 68 07 20 00 	cmpq   $0x0,0x200768(%rip)        # 600e10 <__JCR_END__>
  4006a7:	00 
  4006a8:	74 1e                	je     4006c8 <frame_dummy+0x28>
  4006aa:	b8 00 00 00 00       	mov    $0x0,%eax
  4006af:	48 85 c0             	test   %rax,%rax
  4006b2:	74 14                	je     4006c8 <frame_dummy+0x28>
  4006b4:	55                   	push   %rbp
  4006b5:	bf 10 0e 60 00       	mov    $0x600e10,%edi
  4006ba:	48 89 e5             	mov    %rsp,%rbp
  4006bd:	ff d0                	callq  *%rax
  4006bf:	5d                   	pop    %rbp
  4006c0:	e9 7b ff ff ff       	jmpq   400640 <register_tm_clones>
  4006c5:	0f 1f 00             	nopl   (%rax)
  4006c8:	e9 73 ff ff ff       	jmpq   400640 <register_tm_clones>

00000000004006cd <main>:
main():
/home/guiping/cs241/honorsProjekt/justTestingValgrind.cpp:7
  4006cd:	55                   	push   %rbp
  4006ce:	48 89 e5             	mov    %rsp,%rbp
  4006d1:	89 7d ec             	mov    %edi,-0x14(%rbp)
  4006d4:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
/home/guiping/cs241/honorsProjekt/justTestingValgrind.cpp:8
  4006d8:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
/home/guiping/cs241/honorsProjekt/justTestingValgrind.cpp:9
  4006df:	83 45 f4 01          	addl   $0x1,-0xc(%rbp)
/home/guiping/cs241/honorsProjekt/justTestingValgrind.cpp:10
  4006e3:	83 45 f4 02          	addl   $0x2,-0xc(%rbp)
/home/guiping/cs241/honorsProjekt/justTestingValgrind.cpp:13
  4006e7:	c7 45 f8 0a 00 00 00 	movl   $0xa,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/justTestingValgrind.cpp:15
  4006ee:	8b 45 ec             	mov    -0x14(%rbp),%eax
  4006f1:	83 c0 01             	add    $0x1,%eax
  4006f4:	89 45 fc             	mov    %eax,-0x4(%rbp)
/home/guiping/cs241/honorsProjekt/justTestingValgrind.cpp:17
  4006f7:	b8 00 00 00 00       	mov    $0x0,%eax
/home/guiping/cs241/honorsProjekt/justTestingValgrind.cpp:18
  4006fc:	5d                   	pop    %rbp
  4006fd:	c3                   	retq   

00000000004006fe <_Z41__static_initialization_and_destruction_0ii>:
__static_initialization_and_destruction_0():
  4006fe:	55                   	push   %rbp
  4006ff:	48 89 e5             	mov    %rsp,%rbp
  400702:	48 83 ec 10          	sub    $0x10,%rsp
  400706:	89 7d fc             	mov    %edi,-0x4(%rbp)
  400709:	89 75 f8             	mov    %esi,-0x8(%rbp)
  40070c:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
  400710:	75 27                	jne    400739 <_Z41__static_initialization_and_destruction_0ii+0x3b>
/home/guiping/cs241/honorsProjekt/justTestingValgrind.cpp:18 (discriminator 1)
  400712:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
  400719:	75 1e                	jne    400739 <_Z41__static_initialization_and_destruction_0ii+0x3b>
/usr/include/c++/4.8/iostream:74
  40071b:	bf 51 10 60 00       	mov    $0x601051,%edi
  400720:	e8 7b fe ff ff       	callq  4005a0 <_ZNSt8ios_base4InitC1Ev@plt>
  400725:	ba 48 10 60 00       	mov    $0x601048,%edx
  40072a:	be 51 10 60 00       	mov    $0x601051,%esi
  40072f:	bf d0 05 40 00       	mov    $0x4005d0,%edi
  400734:	e8 87 fe ff ff       	callq  4005c0 <__cxa_atexit@plt>
/home/guiping/cs241/honorsProjekt/justTestingValgrind.cpp:18
  400739:	c9                   	leaveq 
  40073a:	c3                   	retq   

000000000040073b <_GLOBAL__sub_I_main>:
_GLOBAL__sub_I_main():
  40073b:	55                   	push   %rbp
  40073c:	48 89 e5             	mov    %rsp,%rbp
  40073f:	be ff ff 00 00       	mov    $0xffff,%esi
  400744:	bf 01 00 00 00       	mov    $0x1,%edi
  400749:	e8 b0 ff ff ff       	callq  4006fe <_Z41__static_initialization_and_destruction_0ii>
  40074e:	5d                   	pop    %rbp
  40074f:	c3                   	retq   

0000000000400750 <__libc_csu_init>:
__libc_csu_init():
  400750:	41 57                	push   %r15
  400752:	41 89 ff             	mov    %edi,%r15d
  400755:	41 56                	push   %r14
  400757:	49 89 f6             	mov    %rsi,%r14
  40075a:	41 55                	push   %r13
  40075c:	49 89 d5             	mov    %rdx,%r13
  40075f:	41 54                	push   %r12
  400761:	4c 8d 25 90 06 20 00 	lea    0x200690(%rip),%r12        # 600df8 <__frame_dummy_init_array_entry>
  400768:	55                   	push   %rbp
  400769:	48 8d 2d 98 06 20 00 	lea    0x200698(%rip),%rbp        # 600e08 <__init_array_end>
  400770:	53                   	push   %rbx
  400771:	4c 29 e5             	sub    %r12,%rbp
  400774:	31 db                	xor    %ebx,%ebx
  400776:	48 c1 fd 03          	sar    $0x3,%rbp
  40077a:	48 83 ec 08          	sub    $0x8,%rsp
  40077e:	e8 d5 fd ff ff       	callq  400558 <_init>
  400783:	48 85 ed             	test   %rbp,%rbp
  400786:	74 1e                	je     4007a6 <__libc_csu_init+0x56>
  400788:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40078f:	00 
  400790:	4c 89 ea             	mov    %r13,%rdx
  400793:	4c 89 f6             	mov    %r14,%rsi
  400796:	44 89 ff             	mov    %r15d,%edi
  400799:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40079d:	48 83 c3 01          	add    $0x1,%rbx
  4007a1:	48 39 eb             	cmp    %rbp,%rbx
  4007a4:	75 ea                	jne    400790 <__libc_csu_init+0x40>
  4007a6:	48 83 c4 08          	add    $0x8,%rsp
  4007aa:	5b                   	pop    %rbx
  4007ab:	5d                   	pop    %rbp
  4007ac:	41 5c                	pop    %r12
  4007ae:	41 5d                	pop    %r13
  4007b0:	41 5e                	pop    %r14
  4007b2:	41 5f                	pop    %r15
  4007b4:	c3                   	retq   
  4007b5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  4007bc:	00 00 00 00 

00000000004007c0 <__libc_csu_fini>:
__libc_csu_fini():
  4007c0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004007c4 <_fini>:
_fini():
  4007c4:	48 83 ec 08          	sub    $0x8,%rsp
  4007c8:	48 83 c4 08          	add    $0x8,%rsp
  4007cc:	c3                   	retq   
