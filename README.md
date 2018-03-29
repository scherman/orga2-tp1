# Orga 2 - TP1 

Una función para cumplir con la Convención C debe:
- Preservar ```RBX, R12, R13, R14 y R15```
- Retornar el resultado en ```RAX``` o ```XMM0```
- No romper la pila

Los parámetros se pasan (de izquierda a derecha) por los registros
- Si es entero o puntero se pasan respetando el orden usando:
```RDI, RSI, RDX, RCX, R8 y R9```
- Si es de tipo flotante se pasan en los ```XMMs```

Si no hay más registros disponibles se usa la pila, pero deberán
quedar ordenados desde la dirección más baja a la más alta (se
pushean de derecha a izquierda)

| 64-bit register | Lower 32 bits | Lower 16 bits | Lower 8 bits |
| --------------- |:-------------:| -------------:|-------------:|
| rax             | eax           | ax            | al           |
| rbx             | ebx           | bx            | bl           |
| rcx             | ecx           | cx            | cl           |
| rdx             | edx           | dx            | dl           |
| rsi             | esi           | si            | sil          |
| rdi             | edi           | di            | dil          |
| rbp             | ebp           | bp            | bpl          |
| rsp             | esp           | sp            | spl          |
| r8              | r8d           | r8w           | r8b          |
| r9              | r9d           | r9w           | r9b          |
| r10             | r10d          | r10w          | r10b         |
| r11             | r11d          | r11w          | r11b         |
| r12             | r12d          | r12w          | r12b         |
| r13             | r13d          | r13w          | r13b         |
| r14             | r14d          | r14w          | r14b         |
| r15             | r15d          | r15w          | r15b         |

## GDB

1. ```gdb main```
2. Apretar ```CTRL + X + A```
3. ``` layout split```

#### Instrucciones útiles:
- ```info registers```
- ```info registers rdi rsi```
- ``` p $rax```
- ```x/10cb $rdi```
- ```b string_processor.asm:20```