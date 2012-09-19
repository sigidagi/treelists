#ifndef _GENERATOR_H
#define _GENERATOR_H

#include "traits.h"
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>

using std::vector;
using boost::shared_ptr;

// Level 1. Implementation using SFINAE principle.
// this implementation will be "enabled" when the type of parent is the same as child parent.
template<class U, class D> 
void generateChildLists_impl(vector<shared_ptr<U> >& parents, 
                             vector<shared_ptr<D> >& children,
                             typename boost::enable_if_c<boost::is_same<
                                typename FaceTraits<U>::type, 
                                typename FaceTraits<D>::parent
                             >::value>::type* dummy = 0)
{
    /* this is taken when L is level 1 */
    for (size_t l = 0; l < parents.size(); ++l)
    {
        vector<shared_ptr<D> > list = parents[l]->getList(Type2Type<D>());
        children.insert(children.end(), list.begin(), list.end());
    }
}

// Level 2 - Implementation using SFINAE principle.
template<class U, class D> 
void generateChildLists_impl(vector<shared_ptr<U> >& parents, 
                             vector<shared_ptr<D> >& children,
                             typename boost::enable_if_c<boost::is_same<
                                typename FaceTraits<U>::type, 
                                typename FaceTraits<
                                    typename FaceTraits<D>::parent>::parent
                             >::value>::type* dummy = 0)
{
    typedef typename FaceTraits<D>::parent next_parent;

    /* this is taken when L is level 2 */
    for (size_t k = 0; k < parents.size(); ++k)
    {
        vector<shared_ptr<next_parent> > parent1_list = parents[k]->getList(Type2Type<next_parent>());
        for (size_t t = 0; t < parent1_list.size(); ++t)
        {   
            vector<shared_ptr<D> > list = parent1_list[t]->getList(Type2Type<D>());
            children.insert(children.end(), list.begin(), list.end());
        }     
    }   
}

/*
*    // Level 3 -
*    // TODO: 
*    template<class U, class D> 
*    void generateChildLists_impl(vector<const U*>& parents, 
*        vector<const D*>& children,
*        typename boost::enable_if_c<boost::is_same<
*            typename FaceTraits<U*>::type, 
*            typename FaceTraits<
*                typename FaceTraits<
*                    typename FaceTraits<D*>::parent*>::parent*>::parent
*        >::value>::type* dummy = 0)
*    {
*        // TODO: 
*    }
*
*/
// SD: this function should be used, not implementation ...
// a small explanation.
// list elements can contain a other lists. Those other list elements can also contain lists. 
// So, when exist such tree structure, in many case it is convenient to find a list which lies deep down in 
// a tree structure, when parent or list of parents is available. Of course such parent - child relationship should be 
// known in advance. FaceTraits (face_traits.h) classes describes such relationships. 
// As a result we have generic function... and of course it easy portable to other projects when we have
// such tree structure of lists.
//
template<class U, class D>
void getChildList(vector<shared_ptr<U> >& parents, vector<shared_ptr<D> >& children)
{
    children.clear();
    generateChildLists_impl(parents, children);
}

template<class U, class D>
void getChildList(shared_ptr<U> parent, vector<shared_ptr<D> >& children)
{   
    children.clear();
    vector<shared_ptr<U> > single_parent;
    single_parent.push_back(parent);

    generateChildLists_impl(single_parent, children);
}



#endif
