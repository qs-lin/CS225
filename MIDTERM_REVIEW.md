Thoeries review session

# Inheritance

## Base class and derived class

```c++
	class derived : public base {
    
   
  };
```

1. will inherit public members of base class (so remember to write all virtual functions in base public so derived class can inherit and override them)

2. When creating a child object, parent constructor is called first and then child ctor body is executed. So we will put the parent constructor in the initialization list.



### Polymorphism

```c++
Parent *parent = new Child();
// we can only assign child to parent since child is parent
```

### Virtual

A virtual function is a member function declared within base class (with keyword virtual) and is re-defined (overriden) by derived class. It ensures that correct function is called for an object, regardless of the type of reference (or pointer) used for function call.

```c++
parent->myfunc() // will go to Parent.cpp and 
```



### Pure virtual functions

when we have a function that we don't know how to define in the base class

```c++
virtual void myfunc() = 0;
```

### Abstract class

1. when it has at least one pure virtual function (no other special keyword is needed)
2. cannot create an object of this abstract class
3. derived class must override pure virtual functions (inherited from base class) or they will also become abstract classes. 



### Order of Constructor/Destructor



```c++

```

