#pragma once
#include<iostream>
#include"Container.h"
#include"Iterator.h"

template<class Iterator>
concept Iterable = requires(Iterator first, Iterator second) {
    { first == second} -> std::same_as<bool>;             //!!! is_convertible
    { first != second} -> std::same_as<bool>;          //!!! is_convertible
    {*first} -> std::same_as<std::iter_reference_t<Iterator>>;
    *first = *second;
    first = second;
    {++first} -> std::same_as<Iterator&>;
    {--first} -> std::same_as<Iterator&>;
    {first++} -> std::same_as<Iterator>;
    {first--} -> std::same_as<Iterator>;
};


template<class Iterator, class Predicate>
concept ConceptPredicate = requires(Iterator it, Predicate predicate1, Predicate predicate2){
    
    //!!! Не очень понятно, какой смысл сравнивать bool с bool (true == true, false == true и т.д.)
    { predicate1(*it) == predicate2(*it)} -> std::same_as<bool>;
    { predicate1(*it) != predicate2(*it)} -> std::same_as<bool>;
    
    
    
    
    
    {predicate1(*it)} -> std::same_as<bool>; //!!! is_convertible
};

template<class Iterator, class Function>
concept ConceptLambda = requires(Function lambda, Iterator it) {
    lambda(*it);
};

template<class Iterator, class Predicate>
requires Iterable<Iterator> && ConceptPredicate<Iterator, Predicate>
Iterator findIf(Iterator beg, Iterator end, Predicate p) {
    for (; beg != end; ++beg) {
        if (p(*beg)) {
            return beg;
        }
    }

    return end;
}

template <class Iterator, class Function>
requires Iterable<Iterator> && ConceptLambda<Iterator, Function>
Iterator maxElement(Iterator beg, Iterator end, Function comp) {
    Iterator res = beg;
    ++beg;
    for(; beg != end; ++beg) {
        if (comp(*beg) > comp(*res)) { //!!! Неверно. Должен быть бинарный предикат (с проверкой на >)
            res = beg;
        }
    }

    return res;
}

template <class Iterator, class Function>
requires Iterable<Iterator> && ConceptLambda<Iterator, Function>
Iterator minElement(Iterator beg, Iterator end, Function comp) {
    Iterator res = beg;
    ++beg;
    for(; beg != end; ++beg) {
        if (comp(*beg) < comp(*res)) { //!!! Неверно. Должен быть бинарный предикат (с проверкой на <)
            res = beg;
        }
    }

    return res;
}


template <class Iterator, class Function>
requires Iterable<Iterator> && ConceptLambda<Iterator, Function>
void Sort(Iterator beg, Iterator end, Function comp) {
    for (; beg != end; beg++){
        std::iter_swap(beg, minElement(beg, end, comp));
    }
}

template <class Iterator, class Predicate>
requires Iterable<Iterator> && ConceptPredicate<Iterator, Predicate>
void copyIf(Iterator sourceBeg, Iterator sourceEnd, Iterator destBeg, Predicate pred) {
    for(; sourceBeg != sourceEnd; ++sourceBeg){
        if (pred(*sourceBeg)) {
            *destBeg = *sourceBeg;
            ++destBeg;
        }
    }
}


template <class Iterator, class Operation>
requires Iterable<Iterator> && ConceptLambda<Iterator, Operation>
void forEach(Iterator beg, Iterator end, Operation op) {
    for(; beg != end; ++beg) {
        op(*beg);
    }
}
