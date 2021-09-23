# Style Guide for `nodesynth` code

## Prototyping classes and functions

In the header file (`.h` and *not* `.hpp` or `.hh`), all nodesynth related objects should be within `namespace nodesynth`. Within the `.cpp` files, rather than adding `namespace nodesynth { /* code */ }`, at the beginning of the file, we should add the line `using namespace nodesynth;`.

### Function prototypes should look as follows:
Either (A)
```
return_type functionName(
    param_type param1
    , param_type param2
    , param_type param3
);

```
Or, if the return type is particularly long:
```
some_namespace::some_namespace::some_namespace::return_type
functionName(
    param_type param1
    , param_type param2
    , param_type param3
);

```

### Function implementations should look as follows

```
return_type
ClassName::functionName(
    param_type param1
    , param_type param2
    , param_type param3
) {
    /* Code here */
}

```
OR (for short lists of params)
```
return_type
ClassName::functionName(param_type param1, param_type param2) {
    /* Code here */
}

```
## Brackets and Indentation

For loops, if statements, class definitions and namespaces, the following bracket style will be used:
```
namespace nodesynth {
    class SomeClass {
    public:
        SomeClass();
    private:

    protected
        /* Data Members */
        int data;
        int data2;
    };
}
```
```
void
functionName() {
    while (condition) {
        if (condition) {
            /* Code */
        }
    }
}
```
