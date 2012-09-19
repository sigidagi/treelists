/*
 * =====================================================================================
 *
 *       Filename:  traits.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/12/2012 07:46:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef _TRAITS_H
#define _TRAITS_H


class Root;
class A;
class B;
class C;
class D;

template<class T>
struct Type2Type
{
    typedef T original;
};


template<class T>
struct FaceTraits;

template<>
struct FaceTraits <Root>
{
    typedef Root type;
    typedef Root parent;
};

template<>
struct FaceTraits <A>
{
    typedef A type;
    typedef Root parent;
};

template<>
struct FaceTraits <B>
{
    typedef B type;
    typedef A parent;
};

template<>
struct FaceTraits <C>
{
    typedef C type;
    typedef A parent;
};

template<>
struct FaceTraits <D>
{
    typedef D type;
    typedef C parent;
};



#endif
