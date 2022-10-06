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

Pretty cool right? I like to think of Voltt as a bunch of expressions and expressions can be almost anything. Literals, structs, functions, branches and more are all expressions and can be assigned a type and identifier so that the compiler can propery categorize them. That's it, that's Voltt's philosophy. Nothing about memory safety or OOP or being blazingly fast. Just a simple concept that scales from the low level of programming to the highest levels. Right now, I don't have a specific paradigm that I want this language to adopt. I'm maily going to leave it up to the community.  However I do have a checklist that may or may not affect the future of this language.

> ### **1. It will be `Low Level`**
> ### **2. It will prioritize `Zero Cost Abstractions`**
> ### **3. It will have it's own `Standard Library`**
> ### **4. It will prioritize `Generic` and `Functional` programming styles**
> ### **5. It will have very `Limited OOP` support**
> ### **6. It will `Be Fun`**
<br />

# **STOP**
Voltt is currently not in a state where Voltt code can be compiled and run. Everything past this point are proposed features that are subject to change at my whim and fancy

## **Hellol World**

```
entry : fn : {
    println("Hellol")
}
```

Save this snippet to hellol.vlt and run by executing: `voltt run hellol.vlt`

Right away it should be noted that Voltt is a buit quirky. But for now all we need to worry about is that Voltt's way of letting you the programmer know that all is right with the world is by printing "Hellol" to your terminal.


## **Comments**
```
; Single line comment
;;
    Multiline Comment
    ; They can even be nested
;;
```

Here at Voltt, we like to solve problems; So what's the problem here? People argue over the use of semicolons to end statements; But as alot of modern languages have proven that you don't really need semicolons to end statements; The solution? Make semicolons comments so that programmers can have their cake and eat it too;

```
; Having your cake: 
   
    cake :: "Cake"

; Eating it too:

    other_cake :: "Cake but not as good";
```

Brilliant! both are valid Voltt statements and they both will compile to the same machine instructions; Also, I would like to note that I do not expect the issue of programmers arguing over semicolon usage to be solved; In fact I believe that it will get worse after this; However it solve the problem of demonstrating that statement-ending semicolons are useless.

## **Variable Declaration**
The philosophy of Voltt allows variable declaration to have some superpowers. For one, Voltt types are neither constant or mutable by default. You can declare a constant or mutable variable without the use of the const or mut keyword that most other languages adopt. Check this out!

```

x :: 10 ; Constant
y := 10 ; Mutable

; x = 20 INVALID
y = 20; VALID

```

The use of either a colon or a equals sign denots the mutability of the variable. `Colon = const`, `Eq = mut`; Got it? Great! There are a few other aspects about variable declarations to note. For example: If Voltt is statically typed, why do we not have to explicitly provide x and y with a type?
Through the magic of compile-time type inference of course.

```

x :: 10      ; Type : s32
y : s32 : 20 ;- Type : s32

ComplexType : struct : {}

complex :: ComplexType{}


```