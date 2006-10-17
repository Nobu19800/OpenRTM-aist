// -*- C++ -*-
/*!
 * @file SdoConfiguration.cpp
 * @brief SDO's Configuration implementation class
 * @date $Date: 2006-10-17 10:12:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Util.h,v 1.2 2006-10-17 10:12:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/09/11 18:14:53  n-ando
 * The first commit.
 *
 *
 */

#ifndef Util_h
#define Util_h


#include <ace/Guard_T.h>
#include <ace/Thread_Mutex.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <rtm/RTC.h>

typedef ACE_Guard<ACE_Thread_Mutex> Guard;
typedef ACE_Read_Guard<ACE_Thread_Mutex> Read_Guard;
typedef ACE_Write_Guard<ACE_Thread_Mutex> Write_Guard;

typedef ACE_Guard<ACE_Recursive_Thread_Mutex> Guard_r;
typedef ACE_Read_Guard<ACE_Recursive_Thread_Mutex> Read_Guard_r;
typedef ACE_Write_Guard<ACE_Recursive_Thread_Mutex> Write_Guard_r;


template <class T>
struct LockedStruct
{
  ACE_Thread_Mutex lock;
  T                data;
};

/*!
 * @if jp
 * @class SequenceEx
 * @brief CORBA::sequence $B3HD%%/%i%9(B
 *
 * $B$3$N%/%i%9$O(B CORBA $B$N(B sequence $B7?$r3HD%$7(B std::vector $B$N%$%s%?!<%U%'!<%9$r(B
 * $BDs6!$9$k(B ($BNc$($P(B size(), max_size(), empty(), resize(), insert(),
 * erase(), erase_if(), push_back(), pop_back(), find()).
 * CORBA $B$N(B sequence $B7?$r7Q>5$7$F$$$k$?$a!"(BCORBA $B$N(B sequence $B7?$N(B
 * $B%*%Z%l!<%7%g%s(B(like operator=(), maximum(), length(), operator[])$B$b(B
 * $B;HMQ2DG=$G$"$k!#(B
 * .
 * @else
 *
 * @brief CORBA::sequence extention class
 *
 * This class extends CORBA sequence type, and provides std::vector like
 * interfaces (like size(), max_size(), empty(), resize(), insert(),
 * erase(), erase_if(), push_back(), pop_back(), find()).
 * Since this class inherits CORBA sequence class, user can also use CORBA
 * sequence interfaces (like operator=(), maximum(), length(), operator[]).
 *
 * @endif
 */ 
template <class CorbaSequence, class SequenceItem, class Mutex>
class SequenceEx
  : public CorbaSequence
{
public:
  /*!
   * @if jp
   *
   * @brief $B%G%U%)%k%H%3%s%9%H%i%/%?(B
   *
   * $B%G%U%)%k%H%3%s%9%H%i%/%?!#%G%U%)%k%H%3%s%9%H%i%/%?$G$O!"(B
   * $B4pDl%/%i%9$N(BCORBA::sequence $B$ND9$5$r(B 0 $B$K%;%C%H$9$k!#(B
   * 
   * @param CorbaSequence CORBA IDL $B$GDj5A$5$l$k(B sequence $B7A(B
   * @param SeuenceItem CorbaSequence $B$NMWAG7?(B
   * @param Mutex Mutex$B$N7?(B
   *
   * @else
   *
   * @brief Default constructor
   *
   * Default constructor. This default constructor sets the sequence length
   * of CorbaSequence base class.
   *
   * @param CorbaSequence Sequence type defined in CORBA IDL
   * @param SeuenceItem The item type of CorbaSequence
   * @param Mutex The type of mutex
   *
   * @endif
   */
  SequenceEx(): CorbaSequence(0) {};


  /*!
   * @if jp
   *
   * @brief CorbaSequence $B$+$i$N%3%T!<%3%s%9%H%i%/%?(B
   *
   * CorbaSequence$B7?$+$i$N%3%T!<%3%s%9%H%i%/%?!#(B
   * $BM?$($i$l$?(B CorbaSequence $B$NFbMF$r%3%T!<$9$k!#(B
   *
   * @param _sq CorbaSequence $B7A$N%3%T!<85(B
   *
   * @else
   *
   * @brief Copy constructor from CorbaSequence
   *
   * This constructor copies sequence contents from given CorbaSequence
   * to this object.
   *
   * @param _sq Copy source of CorbaSequence type
   *
   * @endif
   */
  SequenceEx(const CorbaSequence& _sq)
    : CorbaSequence(0)
  {
    this->length(_sq.length());
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      (*this)[i] = _sq[i];
  };


  /*!
   * @if jp
   *
   * @brief $B%3%T!<%3%s%9%H%i%/%?(B
   *
   * @param _sq $B%3%T!<85(B
   *
   * @else
   *
   * @brief Copy constructor
   *
   * @param _sq Copy source.
   *
   * @endif
   */
  SequenceEx(const SequenceEx& _sq)
    : CorbaSequence(0)
  {
    this->length(_sq.length());
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      (*this)[i] = _sq[i];
  };


  /*!
   * @if jp
   *
   * @brief $BBeF~1i;;;R(B
   *
   * @param _sq $B%3%T!<85(B
   *
   * @else
   *
   * @brief Assignment operator
   *
   * @param _sq Copy source.
   *
   * @endif
   */
  SequenceEx& operator=(const SequenceEx& _sq)
  {
    this->length(_sq.length());
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      (*this)[i] = _sq[i];
    return *this;
  };


  /*!
   * @if jp
   *
   * @brief CorbaSequence $B$+$i$NBeF~1i;;;R(B
   *
   * @param _sq $B%3%T!<85(B
   *
   * @else
   *
   * @brief Assignment operator from CorbaSequence
   *
   * @param _sq Copy source.
   *
   * @endif
   */
  SequenceEx& operator=(const CorbaSequence& _sq)
  {
    this->length(_sq.length());
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      (*this)[i] = _sq[i];
    return *this;
  };


  /*!
   * @if jp
   *
   * @brief $B%G%9%H%i%/%?(B
   *
   * @else
   *
   * @brief Destructor
   *
   * @endif
   */
  virtual ~SequenceEx()
  {
    this->length(0);
  };


  /*!
   * @if jp
   *
   * @brief $B%5%$%:$r<hF@$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O%7!<%1%s%9$N%5%$%:$rJV$9!#(B
   * CorbaSequence::length() $B$HF1$8!#(B
   *
   * @return $B%7!<%1%s%9$N%5%$%:(B
   *
   * @else
   *
   * @brief Get size of this sequence
   *
   * This operation returns the size of the sequence.
   * This is same as CorbaSequence::length().
   *
   * @return The size of the sequence.
   *
   * @endif
   */
  inline CORBA::ULong size() { return this->length(); }


  /*!
   * @if jp
   *
   * @brief $B3JG<2DG=$J:GBg$N%5%$%:$r<hF@$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O%7!<%1%s%9$N8=:_$N3JG<2DG=$J:GBg$N%5%$%:$rJV$9!#(B
   * CorbaSequence::maximum() $B$HF1$8!#(B
   *
   * @return $B%7!<%1%s%9$K3JG<2DG=$J:GBg$N%5%$%:(B
   *
   * @else
   *
   * @brief Get current maximum size of this sequence
   *
   * This operation returns the current maximum size of the sequence.
   * This is same as CorbaSequence::maximum().
   *
   * @return The maximum size of the sequence.
   *
   * @endif
   */
  inline CORBA::ULong max_size() { return this->maximum(); }


  /*!
   * @if jp
   *
   * @brief $B%7!<%1%s%9$,6u$+$I$&$+D4$Y$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O%7!<%1%s%9$,6u$+$I$&$+$r(B bool $BCM$GJV$9!#(B
   * $B%5%$%:$,(B 0 $B$J$i(B true$B!"$=$&$G$J$1$l$P(B false $B$rJV$9!#(B
   *
   * @return $B%7!<%1%s%9$,6u$+$I$&$+$N(B bool $BCM(B
   *
   * @else
   *
   * @brief Test whether the sequence is empty
   *
   * This operation returns bool value whether the sequence is empty.
   * If the size of the sequence is 0, this operation returns true,
   * and in other case this operation returns false.
   *
   * @return The bool value whether the sequence is empty.
   *
   * @endif
   */
  inline bool empty() { return (this->length() == 0) ? true : false; }


  /*!
   * @if jp
   *
   * @brief $B%7!<%1%s%9$r%j%5%$%:$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O%7!<%1%s%9$ND9$5$rJQ99$9$k!#(B
   * $B8=:_$ND9$5$h$jBg$-$J%5%$%:$,M?$($i$l$?>l9g!"0z?t(B x $B$G!"(B
   * $B?7$?$K%"%m%1!<%H$5$l$?ItJ,$,Kd$a$i$l$k!#(B
   * $B8=:_$ND9$5$h$j>.$5$$%5%$%:$,M?$($i$l$?>l9g!"(BCorabSequence $B$HF1MM$K(B
   * $BM>J,$J%7!<%1%s%9$NMWAG$O:o=|$5$l$k!#(B
   *
   * @param new_size $B?7$7$$%7!<%1%s%9$N%5%$%:(B
   * @param item$B!!D9$/$J$C$?J,$N%7!<%1%s%9$rKd$a$kMWAG(B
   *
   * @else
   *
   * @brief Resize the length of the sequence
   *
   * This operation resizes the length of the sequence.
   * If longer length than current sequence length is given,
   * newly allocated rooms will be assigned by element given by the argument.
   * If shorter length than current sequence length is given,
   * the excessive element of a sequence is deleted like behavior of
   * CorabSequence
   *
   * @param new_size The new size of the sequence
   * @param item$B!!(B   Sequence element to be assigned to new rooms.
   *
   * @endif
   */
  void resize(CORBA::ULong new_size, SequenceItem& item)
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length);
    if (new_size > len) // Widen sequence
      {
	this->length(new_size);
	for (CORBA::ULong i = len; i < new_size; ++i)
	  (*this)[i] = x;
      }
    else if (new_size < len) // shorten sequence
      {
	this->length(new_size);
      }
  }


  /*!
   * @if jp
   *
   * @brief $B%7!<%1%s%9$KMWAG$rA^F~$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O%7!<%1%s%9$NESCf$KMWAG$rA^F~$9$k!#(B
   *
   * @param position $B?7$7$$MWAG$rA^F~$9$k>l=j(B
   * @param item$B!!A^F~$9$k%7!<%1%s%9$NMWAG(B
   *
   * @else
   *
   * @brief Insert a new item to the sequence
   *
   * This operation inserts a new item to the sequence.
   *
   * @param position The position of new inserted item.
   * @param item$B!!(B   Sequence element to be inserted.
   *
   * @endif
   */
  void insert(CORBA::ULong position, const SequenceItem& item)
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length());
    // allowed position: [0, len]
    if (position > len) throw; // InvalidParameter("Invalid index");
    
    // widen sequence
    this->length(len + 1);
    // shift items
    for (CORBA::ULong i = (len - 1); i > position; --i)
      {
	(*this)[i] = (*this)[i-1];
      }
    (*this)[position] = x;
  }


  /*!
   * @if jp
   *
   * @brief $B%7!<%1%s%9$NMWAG$r:o=|$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O%7!<%1%s%9$NMWAG$r:o=|$9$k(B
   *
   * @param position $B:o=|$9$k%7!<%1%s%9MWAG$N>l=j(B
   *
   * @else
   *
   * @brief Erase an item of the sequence
   *
   * This operation erases an item from the sequence.
   *
   * @param position The position of erased item.
   *
   * @endif
   */
  SequenceItem erase(CORBA::ULong position)
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length());
    // allowed position: [0, len)
    if (position > (len - 1)) throw; // InvalidParameter("Invalid index");
    
    // keep erased item
    SequenceItem erased((*this)[position]);
    // shift remaining items
    for (CORBA::ULong i = position; i < (len - 1); ++i)
      {
	(*this)[i] = (*this)[i+1];
      }
    // shorten sequence
    this->length(len - 1);
    return erased;
  }

  /*!
   * @if jp
   *
   * @brief $B%7!<%1%s%9$NMWAG$r=R8l$N$7$?$,$C$F:o=|$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O=R8l$H$7$FM?$($i$l$?4X?t%*%V%8%'%/%H$N(B
   * $B>r7o$,??$N$H$-!"$=$N%7!<%1%s%9$NMWAG$r:o=|$9$k!#(B
   *
   * @param f $B:o=|$9$k%7!<%1%s%9$r7hDj$9$k=Q8l(B
   *
   * @else
   *
   * @brief Erase an item according to the given predicate
   *
   * This operation erases an item according to the given predicate.
   *
   * @param f The predicate functor to decide deletion.
   *
   * @endif
   */
  template <class Predicate>
  SequenceItem erase_if(Predicate f)
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      if (f((*this)[i]))
	return erase(i);
    throw;
  }

  
  /*!
   * @if jp
   *
   * @brief $BMWAG$r:G8eHx$KDI2C$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$OM?$($i$l$?MWAG$r%7!<%1%s%9$N:G8e$KDI2C$9$k!#(B
   *
   * @param item $BDI2C$9$k$9$k%*%V%8%'%/%H(B
   *
   * @else
   *
   * @brief Append an item to the end of the sequence.
   *
   * This operation push back an item to the of the sequence.
   *
   * @param item The object to be added to the end of the sequnce.
   *
   * @endif
   */ 
  void push_back(const SequenceItem& item)
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length());
    this->length(len + 1);
    (*this)[len] = x;
  }

  void pop_back()
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length());
    this->len(len - 1);
  }

  template <class F>
  SequenceItem find(F f) const
  {
    ACE_Read_Guard<Mutex> guard(lock);
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      if (f((*this)[i]))
	return (*this)[i];
    throw; // InvalidParameter("Not found.");
  }

  mutable Mutex lock;
};

/*
template <class CorbaSequence, class F, class SequenceItem>
SequenceItem& erase_if(CorbaSequence& t, F& f)
{
ACE_Write_Guard<Mutex> gaurd(t.lock);
  CORBA::ULong len(t.length());
  for (CORBA::ULong i = 0; i < len; ++i)
    if (f(t[i]))
      return t.erase(i);
}
*/

#endif // Util_h
