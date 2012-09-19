/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/12/2012 07:55:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

#include "generator.h"


using std::vector;
using std::string;
using boost::shared_ptr;


class B
{
    public:
        B(int v) : v_(v) {}
        int id() const { return v_; }

    private:
        int v_;

};

class C 
{
    public:
        C(int v) : v_(v) 
        {
            listD_.push_back(boost::make_shared<D>("foo"));
            listD_.push_back(boost::make_shared<D>("bar"));
        }
        int number() const { return v_; }
        vector<shared_ptr<D> > getList(Type2Type<D>) { return listD_; }

    private:
        int v_;
        vector<shared_ptr<D> > listD_;
};

class D
{
    public:
        D(string name) : name_(name) {}
        string name() const { return name_; }

    private:
        string name_;
};

class A
{
    public:
        A(int v) : v_(v) 
        {
            listB_.push_back( boost::make_shared<B>(v_ + 10) );
            listB_.push_back( boost::make_shared<B>(v_ + 20) );
            listB_.push_back( boost::make_shared<B>(v_ + 30) );
            listB_.push_back( boost::make_shared<B>(v_ + 40) );

            listC_.push_back( boost::make_shared<C>(v_ + 100) );
            listC_.push_back( boost::make_shared<C>(v_ + 200) );
            listC_.push_back( boost::make_shared<C>(v_ + 300) );
            listC_.push_back( boost::make_shared<C>(v_ + 400) );
            listC_.push_back( boost::make_shared<C>(v_ + 500) );

        }
        int id() const { return v_; }

        vector<shared_ptr<B> > getList(Type2Type<B>) { return listB_; }
        vector<shared_ptr<C> > getList(Type2Type<C>) { return listC_; }
    
    private:
        vector<shared_ptr<B> > listB_;
        vector<shared_ptr<C> > listC_;

        int v_;
    
};


class Root
{
    public:
        static Root& instance() {
            static Root root_;
            return root_;
        }
       
        // to suport uniform interface.
        vector<shared_ptr<A> > getList(Type2Type<A>) { return listA_; }

    private:
        Root() 
        {
            listA_.push_back(boost::make_shared<A>(2));
            listA_.push_back(boost::make_shared<A>(3));
            listA_.push_back(boost::make_shared<A>(4));
        }

        Root(Root const&);
        Root& operator=(Root const&);
        
        vector<shared_ptr<A> > listA_;
        
};

int main()
{
    // just a test that we have a list.
    vector<shared_ptr<A> > listA = Root::instance().getList(Type2Type<A>());

/*
 *    vector<shared_ptr<B> > listB;
 *    getChildList(listA, listB);
 *    
 *    std::ostream_iterator<int> out_it(std::cout, " ");
 *    std::transform(listB.begin(), listB.end(), out_it, boost::bind(&B::id, _1)); 
 *
 *    std::cout << std::endl;
 */

    vector<shared_ptr<D> > listD;
    getChildList(listA, listD);
    std::ostream_iterator<string> out_it(std::cout, " ");
    std::transform(listD.begin(), listD.end(), out_it, boost::bind(&D::name, _1)); 

    std::cout << std::endl;
    
    /*
     *vector<shared_ptr<B> > list = listA[0]->getList(Type2Type<B>());
     *vector<shared_ptr<D> > listD;
     *getChildList(listB, listD);
     */


    return 0;
}
