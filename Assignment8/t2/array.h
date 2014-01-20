//==========================================================================
// array.h : Dynamic array class template.
//==========================================================================
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdlib.h>
#include <string.h>

template< class Type >
class Array {
  public:
    Array( ) { length = 0; max_length = 0; array = NULL; }
    Array( const Array<Type>& l )
    {
        *this = l;
        if( max_length != 0 ) {
            array = new Type[max_length];
            memcpy( (void*)array, (void*)l.Data(), max_length*sizeof(Type) );
        } else {
            array = NULL;
        }
    }

    ~Array( )
    {
        delete [] array;
    }

 // Copy functions
    void Copy( const Array<Type>& l )
    {
        if( array != NULL ) {
            Destroy();
        }
        length = l.Length();
        max_length = l.Max_Length();
        if( max_length != 0 ) {
            array = new Type[max_length];
            memcpy( (void*)array, (void*)l.Data(), max_length*sizeof(Type) );
        } else {
            array = NULL;
        }
    }
    void Copy_Length( const Array<Type>& l )
    {
        if( array != NULL ) {
            Destroy();
        }
        length = l.Length();
        max_length = l.Length();
        if( max_length != 0 ) {
            array = new Type[max_length];
            memcpy( (void*)array, (void*)l.Data(), max_length*sizeof(Type) );
        } else {
            array = NULL;
        }
    }

  // Content Query
    int Length( ) const { return length; }
    int Max_Length( ) const { return max_length; }
    Type& operator[]( int index )
    {
        return array[index];
    }
    Type& Last( ) { return array[length-1]; }
    Type* operator()( int index )
    {
        return array+index;
    }
    Type* Data( ) const { return array; }
    int Position( Type* addr ) const { return (int)(addr-array); }
    bool Empty( ) const { return length == 0; }

  // Content modification
    void Set_Last( Type& t ) { array[length-1] = t; }
    void Add( Type t ) 
    {
      array[length++] = t;
    }
    void Add_Grow( Type t, int amount ) 
    {
        if( length == max_length ) {
            Grow( amount );
        }
        Add( t );
    }
    void Set_Length( int len ) { length = len; }
    void Increment_Length( ) { length++; }
    void Decrement_Length( ) { length--; }
    void Nullify( ) { array = NULL; length = 0; max_length = 0; }

  // Creation/allocation and destroy
    void Create( int n )
    {
        if( max_length != 0 ) {
            length = max_length = 0;
            Destroy();
        }
        if( n != 0 ) {
            array = new Type[n]; length = n; max_length = n;
        }
    }
    void Destroy( )
    {
        delete [] array;
        array = NULL; length = 0; max_length = 0;
    }

  // Growing
    void Grow( int amount )
    {
        Type* temp = array;
        array = new Type[max_length+amount];
        // Copy the old elements back
        memcpy( (void*)array, (void*)temp, length*sizeof(Type) );
        max_length += amount;
    }
    void Grow_Double( )
    {
        if( length != 0 ) {
            Type* temp = array;
            array = new Type[max_length<<1];
            // Copy the old elements back
            memcpy( (void*)array, (void*)temp, length*sizeof(Type) );
            max_length <<= 1;
        }
    }

  private:
    int length;
    int max_length;
    Type* array;
};

#endif
