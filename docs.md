# **Voltt Documentation**

## **Introduction**

Voltt is a statically typed comiled language designed to be expressive and explicit

## **Installing Voltt**

Currently, the Voltt compiler can be natively build on x86-64 linux using the build.sh file.
This should work on any Unix system that has the llvm toolchain installed.

## **Voltt's Philosophy**
> **EVERYTHING IS AN EXPRESSION** <br />

Voltt follows a similar pattern that [Odin](https://odin-lang.org/) and [Jai](https://en.wikipedia.org/?title=JAI_(programming_language)&redirect=no) adopt for variable declaration and a few other things. But Voltt takes that sytax to the next level. Here's some Voltt code as well as C equivalents to demonstrate.

**Expression Declaration in theory:**
```
    ; `identifier` : `type` `mutability` `expression`
```

**Variable Declaration in practice:**
```
    x : s32 : 69
```

**C Equivalent:**
```
    const int x = 69;
```

**Function Declaration in practice:**
```
    add : fn(a: s32, b: s32) -> s32 : {
        ret a + b
    }
```

**C Equivalent:**
```
    int add(int a, int b) {
        return a + b;
    }
```

Pretty cool right? I like to think of Voltt as a collection of expression. Variables, structures, functions, branches and more are all expressions and can be assigned a type as well as an identifier so that the compiler can propery categorize them. That's it, that's Voltt's philosophy. Nothing about memory safey, high performance, or gimmicky features. Just a simple concept that scales from the low level of programming to the highest levels. Right now, I don't have a specific paradigm that I want this language to adopt. I'm maily going to leave it up to the community. However I do have a checklist that may or may not affect the future of this language.

> ### **1. It will be `Low Level`**
> ### **2. It will prioritize `Zero Cost Abstractions`**
> ### **3. It will have it's own `Standard Library`**
> ### **4. It will prioritize `Generic` and `Functional` programming styles**
> ### **5. It will have very `Limited OOP` support**
> ### **6. It will allow the programmer to interface with the compiler**
> ### **7. It will `Be Fun`**
<br />

# **STOP**

Voltt is mainly just a concept. There is no way to compile and run Voltt code. Everything past this point are proposed features that are subject to change at my whim and fancy.

## **Hellol World**

```
entry : fn : {
    println("Hellol")
}
```

Save this snippet to hellol.vlt and run by executing: `voltt run hellol.vlt`

Right away it should be noted that Voltt is a bit quirky. But for now, all we need to worry about is the nice greeting we get from running this code snippet.

## **Comments**

```
; Single line comment
;;
    Multiline Comment
    ; They can even be nested
;;
```

Here at Voltt, we like to solve problems; So what's the problem here? People sometimes argue whether or not semicolons should be used to end statementss; Nowadays modern langauges (Python, Go, etc.) have proven that you don't really need semicolons to end statements; The solution to this problem? Make semicolons comments so that programmers can have their cake and eat it too;

```
; Having your cake: 
   
    cake :: "Cake"

; Eating it too:

    other_cake :: "Cake but not as good";
```

Brilliant! Both of the examples shown above are valid Voltt statements and they will both compile; Also, I would like to note that I do not expect the issue of programmers arguing over semicolon usage to be solved; In fact I believe that it will get much worse after this; However, it does demonstrate that using semicolons to end statements are effectively useless; So in this case, we have solved the problem of leading the horse to water, but now we can only hope that it will drink;

## **Variable Declaration**

### **Constant and Mutable**
The philosophy of Voltt allows variable declarations to have some superpowers. For one, Voltt types are neither constant or mutable by default. You can declare a constant or mutable variable without the use of the const or mut keyword that most other languages adopt. Check this out!

```
x :: 10 ; Constant
y := 10 ; Mutable

x = 20; INVALID
y = 20; VALID
```

The use of either a colon or a equals sign denots the mutability of the variable. `Colon = const`, `Eq = mut`; Got it? Great! 

### **Type Inference**

There are a few other aspects about variable declarations to note. For example: If Voltt is statically typed, why do we not have to explicitly provide x and y with a type?
Through the magic of compile-time type inference of course. In most cases, Voltt can assume the type of a variable at compile time and automatically assign it. However, Voltt still gives the programmer the ability to specifically assign types to different expressions.

```
x :: 10; Equivalent to x : s32 : 10

y :: 'A'; Equivalent to y : char : 'A'
```

Even when it comes to assigning types of more complex data types, Voltt still has the ability to inference the type of the expression being assigned to the variable.

## **Functions**

Functions in Voltt are a bit different than what is found is most other languages. Because functions are a type, when they are declared, we must provide the parameters and return type of the function inside of an expression's type field.

```
foo : fn(a: s32, b: s32) -> s32 {
    ret a + b
}

bar : fn(a: s32, b: s32) -> s32 {
    ret a - b
}
```

In this case foo and bar are both functions that take two parameters that are both signed 32 bit integers and returns one as well. Sometimes functions act as subroutines and don't require the need for paremeters or a return type.

```
no_return : fn : {
    println("This function is more of a subroutine")
}
```

That's all well and good, but how are we supposed to specify wether or not function parameters and their return types are constant or mutable. This is a great point and is probably something that can be solved more cleverly. For now, Voltt assumes all function parameters are constant and need to be declared mutable using the `mut` keyword.

```
is_mutable : fn(a: mut s32) -> mut s32 {
    ret a += 10

;;
The value of `is_mutable` a can be changed within the function and the return value can also be mutated in within the scope of the caller.
;;
```

## **Voltt Types**
### **Primatives**
```
; Booleans:
    
    bool

; Integers:

    s8 s16 s32 s64
    u8 u16 u32 u64

    ssize  ; How many bytes it takes to reference a location in memory
    usize

; Floating Point:

    d32 d64 d128

; Characters:

    rune ; Represents a unicode charater
    char ; Represents an ascii character
 
```