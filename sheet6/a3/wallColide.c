loc_41EC6C:                             ; CODE XREF: Spell::Spell(SpellType,int)+32A↑j
                                        ; DATA XREF: .rodata:off_43CA64↓o
                lea     rax, [rbp+var_D1] ; jumptable 000000000041EC6A case 0
                mov     rdi, rax
                call    __ZNSaIcEC1Ev   ; std::allocator<char>::allocator(void)
                lea     rdx, [rbp+var_D1]
                lea     rax, [rbp+var_100]
                lea     rsi, aSpellsEyeActiv ; "spells/eye_active.png"
                mov     rdi, rax
                call    __ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_ ; std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string(char const*,std::allocator<char> const&)
                lea     rax, [rbp+var_100]
                mov     esi, 1          ; buildMipmaps
                mov     rdi, rax        ; filename
                call    _Z11loabasic_stringIcSt11char_traitsIcESaIcEEEb ; loabasic_string<char,std::char_traits<char>,std::allocator<char>> const&,bool)
                lea     rax, [rbp+var_100]
                mov     rdi, rax
                call    _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev ; std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::~basic_string()
                lea     rax, [rbp+var_D1]
                mov     rdi, rax
                call    __ZNSaIcED1Ev   ; std::allocator<char>::~allocator()
                jmp     loc_41EE27      ; jumptable 000000000041EC6A default case
; ---------------------------------------------------------------------------
loc_41ECCF:                             ; CODE XREF: Spell::Spell(SpellType,int)+32A↑j
                                        ; DATA XREF: .rodata:off_43CA64↓o
                lea     rax, [rbp+var_A1] ; jumptable 000000000041EC6A case 1
                mov     rdi, rax
                call    __ZNSaIcEC1Ev   ; std::allocator<char>::allocator(void)
                lea     rdx, [rbp+var_A1]
                lea     rax, [rbp+var_D0]
                lea     rsi, aSpellsEagleAct ; "spells/eagle_active.png"
                mov     rdi, rax
                call    __ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_ ; std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string(char const*,std::allocator<char> const&)
                lea     rax, [rbp+var_D0]
                mov     esi, 1          ; buildMipmaps
                mov     rdi, rax        ; filename
                call    _Z11loabasic_stringIcSt11char_traitsIcESaIcEEEb ; loabasic_string<char,std::char_traits<char>,std::allocator<char>> const&,bool)
                lea     rax, [rbp+var_D0]
                mov     rdi, rax
                call    _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev ; std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::~basic_string()
                lea     rax, [rbp+var_A1]
                mov     rdi, rax
                call    __ZNSaIcED1Ev   ; std::allocator<char>::~allocator()
                jmp     loc_41EE27      ; jumptable 000000000041EC6A default case
; ---------------------------------------------------------------------------
loc_41ED32:                             ; CODE XREF: Spell::Spell(SpellType,int)+32A↑j
                                        ; DATA XREF: .rodata:off_43CA64↓o
                lea     rax, [rbp+var_71] ; jumptable 000000000041EC6A case 2
                mov     rdi, rax
                call    __ZNSaIcEC1Ev   ; std::allocator<char>::allocator(void)
                lea     rdx, [rbp+var_71]
                lea     rax, [rbp+var_A0]
                lea     rsi, aSpellsHorseAct ; "spells/horse_active.png"
                mov     rdi, rax
                call    __ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_ ; std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string(char const*,std::allocator<char> const&)
                lea     rax, [rbp+var_A0]
                mov     esi, 1          ; buildMipmaps
                mov     rdi, rax        ; filename
                call    _Z11loabasic_stringIcSt11char_traitsIcESaIcEEEb ; loabasic_string<char,std::char_traits<char>,std::allocator<char>> const&,bool)
                lea     rax, [rbp+var_A0]
                mov     rdi, rax
                call    _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev ; std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::~basic_string()
                lea     rax, [rbp+var_71]
                mov     rdi, rax
                call    __ZNSaIcED1Ev   ; std::allocator<char>::~allocator()
                jmp     loc_41EE27      ; jumptable 000000000041EC6A default case
; ---------------------------------------------------------------------------
loc_41ED8C:                             ; CODE XREF: Spell::Spell(SpellType,int)+32A↑j
                                        ; DATA XREF: .rodata:off_43CA64↓o
                lea     rax, [rbp+var_41] ; jumptable 000000000041EC6A case 3
                mov     rdi, rax
                call    __ZNSaIcEC1Ev   ; std::allocator<char>::allocator(void)
                lea     rdx, [rbp+var_41]
                lea     rax, [rbp+var_70]
                lea     rsi, aSpellsWingfoot_0 ; "spells/wingfoot_active.png"
                mov     rdi, rax
                call    __ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_ ; std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string(char const*,std::allocator<char> const&)
                lea     rax, [rbp+var_70]
                mov     esi, 1          ; buildMipmaps
                mov     rdi, rax        ; filename
                call    _Z11loabasic_stringIcSt11char_traitsIcESaIcEEEb ; loabasic_string<char,std::char_traits<char>,std::allocator<char>> const&,bool)
                lea     rax, [rbp+var_70]
                mov     rdi, rax
                call    _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev ; std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::~basic_string()
                lea     rax, [rbp+var_41]
                mov     rdi, rax
                call    __ZNSaIcED1Ev   ; std::allocator<char>::~allocator()
                jmp     short loc_41EE27 ; jumptable 000000000041EC6A default case
; ---------------------------------------------------------------------------
loc_41EDDA:                             ; CODE XREF: Spell::Spell(SpellType,int)+32A↑j
                                        ; DATA XREF: .rodata:off_43CA64↓o
                lea     rax, [rbp+var_11] ; jumptable 000000000041EC6A case 4
                mov     rdi, rax
                call    __ZNSaIcEC1Ev   ; std::allocator<char>::allocator(void)
                lea     rdx, [rbp+var_11]
                lea     rax, [rbp+var_40]
                lea     rsi, aSpellsSunActiv ; "spells/sun_active.png"
                mov     rdi, rax
                call    __ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_ ; std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string(char const*,std::allocator<char> const&)
                lea     rax, [rbp+var_40]
                mov     esi, 1          ; buildMipmaps
                mov     rdi, rax        ; filename
                call    _Z11loabasic_stringIcSt11char_traitsIcESaIcEEEb ; loabasic_string<char,std::char_traits<char>,std::allocator<char>> const&,bool)
                lea     rax, [rbp+var_40]
                mov     rdi, rax
                call    _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev ; std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::~basic_string()
                lea     rax, [rbp+var_11]
                mov     rdi, rax
                call    __ZNSaIcED1Ev   ; std::allocator<char>::~allocator()
                nop