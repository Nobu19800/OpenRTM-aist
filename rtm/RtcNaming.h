// -*- C++ -*-
/*!
 * @file RtcNaming.h
 * @brief naming Service helper class
 * @date $Date: 2006-09-11 18:26:20 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcNaming.h,v 1.3 2006-09-11 18:26:20 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2005/05/16 06:29:05  n-ando
 * - RtcNaming class was DLL exported for Windows port.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */


#ifndef RtcNaming_h
#define RtcNaming_h

// CORBA header include
//#include "rtm/idl/RTMBaseStub.h"
//#include "rtm/idl/RTMBaseSkel.h"
//#include "rtm/RtcBase.h"
#include "rtm/RTC.h"
#ifdef ORB_IS_OMNIORB
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#include "omniORB4/CORBA.h"
//#include "omniORB4/Naming.h"
#endif

// STL includes
#include <map>
#include <string>
#include <vector>

namespace RTM
{

  class RtcCorbaNaming
  {
  public:
    RtcCorbaNaming(CORBA::ORB_ptr orb, const char* name_server);
    virtual ~RtcCorbaNaming(){};

    typedef CosNaming::NamingContext::NotFound      NotFound;
    typedef CosNaming::NamingContext::CannotProceed CannotProceed;
    typedef CosNaming::NamingContext::InvalidName   InvalidName;
    typedef CosNaming::NamingContext::AlreadyBound  AlreadyBound;
    typedef CosNaming::NamingContext::NotEmpty      NotEmpty;
    typedef CosNaming::NamingContextExt::InvalidAddress InvalidAddress;
    typedef std::vector<CORBA::Object_ptr> ObjectList;

    /*!
     * @if jp
     *
     * @brief Object $B$r(B bind $B$9$k(B
     *
     * CosNaming::bind() $B$H$[$\F1Ey$NF/$-$r$9$k$,!">o$KM?$($i$l$?%M!<%`%5!<%P$N(B
     * $B%k!<%H%3%s%F%-%9%H$KBP$7$F(Bbind()$B$,8F$S=P$5$l$kE@$,0[$J$k!#(B
     *
     * Name <name> $B$H(B Object <obj> $B$rEv3:(B NamingContext $B>e$K%P%$%s%I$9$k!#(B
     * c_n $B$,(B n $BHVL\$N(B NameComponent $B$r$"$i$o$9$H$9$k$H!"(B
     * name $B$,(B n $B8D$N(B NameComponent $B$+$i@.$k$H$-!"0J2<$N$h$&$K07$o$l$k!#(B
     *
     * cxt->bind(<c_1, c_2, ... c_n>, obj) $B$O0J2<$NA`:n$HF1Ey$G$"$k!#(B
     * cxt->resolve(<c_1, ... c_(n-1)>)->bind(<c_n>, obj)
     *
     * $B$9$J$o$A!"(B1$BHVL\$+$i(Bn-1$BHVL\$N%3%s%F%-%9%H$r2r7h$7!"(Bn-1$BHVL\$N%3%s%F%-%9%H(B
     * $B>e$K(B name <n> $B$H$7$F!!(Bobj $B$r(B bind $B$9$k!#(B
     * $BL>A02r7h$K;22C$9$k(B <c_1, ... c_(n-1)> $B$N(B NemingContext $B$O!"(B
     * bindContext() $B$d(B rebindContext() $B$G4{$K%P%$%s%I:Q$_$G$J$1$l$P$J$i$J$$!#(B
     * $B$b$7(B <c_1, ... c_(n-1)> $B$N(B NamingContext $B$,B8:_$7$J$$>l9g$K$O!"(B
     * NotFound $BNc30$,H/@8$9$k!#(B
     *
     * $B$?$@$7!"6/@)%P%$%s%I%U%i%0(B force $B$,(B true $B$N;~$O!"(B<c_1, ... c_(n-1)>
     * $B$,B8:_$7$J$$>l9g$K$b!":F5"E*$K%3%s%F%-%9%H$r%P%$%s%I$7$J$,$i!"(B
     * $B:G=*E*$K(B obj $B$rL>A0(B name <c_n> $B$K%P%$%s%I$9$k!#(B
     *
     * $B$$$:$l$N>l9g$G$b!"(Bn-1$BHVL\$N%3%s%F%-%9%H>e$K(B name<n> $B$N%*%V%8%'%/%H(B
     * (Object $B$"$k$$$O(B $B%3%s%F%-%9%H(B) $B$,%P%$%s%I$5$l$F$$$l$P(B
     * AlreadyBound $BNc30$,H/@8$9$k!#(B
     *
     * @param name $B%*%V%8%'%/%H$KIU$1$kL>A0$N(B NameComponent
     * @param obj $B4XO"IU$1$i$l$k(B Object
     * @param force true$B$N>l9g!"ESCf$N%3%s%F%-%9%H$r6/@)E*$K%P%$%s%I$9$k(B
     *
     * @exception NotFound $BESCf$N(B <c_1, c_2, ..., c_(n-1)> $B$,B8:_$7$J$$!#(B
     * @exception CannotProceed $B2?$i$+$NM}M3$G=hM}$r7QB3$G$-$J$$!#(B
     * @exception InvalidName $B0z?t(B name $B$NL>A0$,IT@5!#(B
     * @exception AlreadyBound name <c_n> $B$N(B Object $B$,$9$G$K%P%$%s%I$5$l$F$$$k!#(B
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bind(const CosNaming::Name& name, CORBA::Object_ptr obj,
	      const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);


    /*!
     * @if jp
     *
     * @brief Object $B$r(B bind $B$9$k(B
     *
     * Object $B$r(B bind $B$9$k:]$KM?$($kL>A0$,J8;zNsI=8=$G$"$k$3$H0J30$O!"(Bbind()
     * $B$HF1$8$G$"$k!#(Bbind(toName(string_name), obj) $B$HEy2A!#(B
     *
     * @param string_name $B%*%V%8%'%/%H$KIU$1$kL>A0$NJ8;zNsI=8=(B
     * @param obj $B4XO"IU$1$i$l$k%*%V%8%'%/%H(B
     * @param force true$B$N>l9g!"ESCf$N%3%s%F%-%9%H$r6/@)E*$K%P%$%s%I$9$k(B
     *
     * @exception NotFound $BESCf$N(B <c_1, c_2, ..., c_(n-1)> $B$,B8:_$7$J$$!#(B
     * @exception CannotProceed $B2?$i$+$NM}M3$G=hM}$r7QB3$G$-$J$$!#(B
     * @exception InvalidName $B0z?t(B name $B$NL>A0$,IT@5!#(B
     * @exception AlreadyBound name <n> $B$N(B Object $B$,$9$G$K%P%$%s%I$5$l$F$$$k!#(B
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindByString(const char* string_name, CORBA::Object_ptr obj,
		      const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief $BESCf$N%3%s%F%-%9%H$r(B bind $B$7$J$,$i(B Object $B$r(B bind $B$9$k(B
     *
     * context $B$GM?$($i$l$?(B NamingContext $B$KBP$7$F!"(Bname $B$G;XDj$5$l$?(B
     * $B%M!<%`%3%s%]!<%M%s%H(B <c_1, ... c_(n-1)> $B$r(B NamingContext $B$H$7$F(B
     * $B2r7h$7$J$,$i!"L>A0(B <c_n> $B$KBP$7$F(B obj $B$r(B bind $B$9$k!#(B
     * $B$b$7!"(B<c_1, ... c_(n-1)> $B$KBP1~$9$k(B NamingContext $B$,$J$$>l9g$K$O(B
     * $B?7$?$J(B NamingContext $B$r%P%$%s%I$9$k!#(B
     *
     * $B:G=*E*$K(B <c_1, c_2, ..., c_(n-1)> $B$KBP1~$9$k(B NamingContext $B$,@8@.(B
     * $B$^$?$O2r7h$5$l$?>e$G!"(BCosNaming::bind(<c_n>, object) $B$,8F$S=P$5$l$k!#(B
     * $B$3$N$H$-!"$9$G$K%P%$%s%G%#%s%0$,B8:_$9$l$P(B AlreadyBound$BNc30$,H/@8$9$k!#(B
     *
     * $BESCf$N%3%s%F%-%9%H$r2r7h$9$k2aDx$G!"2r7h$7$h$&$H$9$k%3%s%F%-%9%H$H(B
     * $BF1$8L>A0$N(B NamingContext $B$G$O$J$$(B Binding $B$,B8:_$9$k>l9g!"(B
     * CannotProceed $BNc30$,H/@8$7=hM}$rCf;_$9$k!#(B
     *
     * @param context bind $B$r3+;O$9$k!!(BNamingContext
     * @param name $B%*%V%8%'%/%H$KIU$1$kL>A0$N%M!<%`%3%s%]!<%M%s%H(B
     * @param obj $B4XO"IU$1$i$l$k%*%V%8%'%/%H(B
     *
     * @exception CannotProceed <c_1, ..., c_(n-1)> $B$KBP1~$9$k(B NamingContext 
     *            $B$N$&$A$R$H$D$,!"$9$G$K(B NamingContext $B0J30$N(B object $B$K%P%$%s%I(B
     *            $B$5$l$F$*$j!"=hM}$r7QB3$G$-$J$$!#(B
     * @exception InvalidName $BL>A0(B name $B$,IT@5(B
     * @exception AlreadyBound name <c_n> $B$K$9$G$K2?$i$+$N(B object $B$,%P%$%s%I(B
     *            $B$5$l$F$$$k!#(B
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindRecursive(CosNaming::NamingContext_ptr context,
		       const CosNaming::Name& name,
		       CORBA::Object_ptr obj)
      throw(CannotProceed, InvalidName, AlreadyBound);



    /*!
     * @if jp
     *
     * @brief Object $B$r(B rebind $B$9$k(B
     *
     * name $B$G;XDj$5$l$?(B Binding $B$,$9$G$KB8:_$9$k>l9g$r=|$$$F(B bind() $B$HF1$8(B
     * $B$G$"$k!#%P%$%s%G%#%s%0$,$9$G$KB8:_$9$k>l9g$K$O!"?7$7$$%P%$%s%G%#%s%0$K(B
     * $BCV$-49$($i$l$k!#(B
     *
     * @param name $B%*%V%8%'%/%H$KIU$1$kL>A0$N(B NameComponent
     * @param obj $B4XO"IU$1$i$l$k%*%V%8%'%/%H(B
     * @param force true$B$N>l9g!"ESCf$N%3%s%F%-%9%H$r6/@)E*$K%P%$%s%I$9$k(B
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebind(const CosNaming::Name& name, CORBA::Object_ptr obj,
		const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);


    /*!
     * @if jp
     *
     * @brief Object $B$r(B rebind $B$9$k(B
     *
     * Object $B$r(B rebind $B$9$k:]$KM?$($kL>A0$,J8;zNsI=8=$G$"$k$3$H0J30$O(B rebind()
     * $B$HF1$8$G$"$k!#(Brebind(toName(string_name), obj) $B$HEy2A!#(B
     *
     * @param string_name $B%*%V%8%'%/%H$KIU$1$kL>A0$NJ8;zNsI=8=(B
     * @param obj $B4XO"IU$1$i$l$k%*%V%8%'%/%H(B
     * @param force true$B$N>l9g!"ESCf$N%3%s%F%-%9%H$r6/@)E*$K%P%$%s%I$9$k(B
     *
     * @exception NotFound $BESCf$N(B <c_1, c_2, ..., c_(n-1)> $B$,B8:_$7$J$$!#(B
     * @exception CannotProceed $B2?$i$+$NM}M3$G=hM}$r7QB3$G$-$J$$!#(B
     * @exception InvalidName $B0z?t(B name $B$NL>A0$,IT@5!#(B
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindByString(const char* string_name, CORBA::Object_ptr obj,
			const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);

    
    /*!
     * @if jp
     *
     * @brief $BESCf$N%3%s%F%-%9%H$r(B bind $B$7$J$,$i(B Object $B$r(B rebind $B$9$k(B
     *
     * name <c_n> $B$G;XDj$5$l$?(B NamingContext $B$b$7$/$O(B Object $B$,$9$G$KB8:_$9$k(B
     * $B>l9g$r=|$$$F(B bindRecursive() $B$HF1$8$G$"$k!#(B
     *
     * name <c_n> $B$G;XDj$5$l$?%P%$%s%G%#%s%0$,$9$G$KB8:_$9$k>l9g$K$O!"(B
     * $B?7$7$$%P%$%s%G%#%s%0$KCV$-49$($i$l$k!#(B
     *
     * @param name $B%*%V%8%'%/%H$KIU$1$kL>A0$NJ8;zNsI=8=(B
     * @param obj $B4XO"IU$1$i$l$k%*%V%8%'%/%H(B
     * @param force true$B$N>l9g!"ESCf$N%3%s%F%-%9%H$r6/@)E*$K%P%$%s%I$9$k(B
     *
     * @exception CannotProceed $BESCf$N%3%s%F%-%9%H$,2r7h$G$-$J$$!#(B
     * @exception InvalidName $BM?$($i$l$?(B name $B$,IT@5!#(B
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindRecursive(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name,
			 CORBA::Object_ptr obj)
      throw(CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief NamingContext $B$r(B bind $B$9$k(B
     *
     * bind $B$5$l$k%*%V%8%'%/%H$,(B NamingContext $B$G$"$k$3$H$r=|$$$F(B bind() 
     * $B$HF1$8$G$"$k!#(B
     *
     * @param name $B%*%V%8%'%/%H$KIU$1$kL>A0$N%M!<%`%3%s%]!<%M%s%H(B
     * @param name_cxt $B4XO"IU$1$i$l$k(B NamingContext
     * @param force true$B$N>l9g!"ESCf$N%3%s%F%-%9%H$r6/@)E*$K%P%$%s%I$9$k(B
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindContext(const CosNaming::Name& name,
		     CosNaming::NamingContext_ptr name_cxt,
		     const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief NamingContext $B$r(B bind $B$9$k(B
     *
     * bind $B$5$l$k%*%V%8%'%/%H$,(B NamingContext $B$G$"$k$3$H$r=|$$$F(B bind() 
     * $B$HF1$8$G$"$k!#(B
     *
     * @param name $B%*%V%8%'%/%H$KIU$1$kL>A0$NJ8;zNsI=8=(B
     * @param name_cxt $B4XO"IU$1$i$l$k(B NamingContext
     * @param force true$B$N>l9g!"ESCf$N%3%s%F%-%9%H$r6/@)E*$K%P%$%s%I$9$k(B
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindContext(const char* string_name,
		     CosNaming::NamingContext_ptr name_cxt,
		     const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief NamingContext $B$r(B bind $B$9$k(B
     *
     * bind $B$5$l$k%*%V%8%'%/%H$,(B NamingContext $B$G$"$k$3$H$r=|$$$F(B
     * bindRecursive() $B$HF1$8$G$"$k!#(B
     *
     * @param context bind $B$r3+;O$9$k!!(BNamingContext
     * @param name $B%*%V%8%'%/%H$KIU$1$kL>A0$N%M!<%`%3%s%]!<%M%s%H(B
     * @param name_cxt $B4XO"IU$1$i$l$k(B NamingContext
     * @param force true$B$N>l9g!"ESCf$N%3%s%F%-%9%H$r6/@)E*$K%P%$%s%I$9$k(B
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindContextRecursive(CosNaming::NamingContext_ptr context,
			      const CosNaming::Name& name,
			      CosNaming::NamingContext_ptr name_cxt);
    /*!
     * @if jp
     *
     * @brief NamingContext $B$r(B rebind $B$9$k(B
     *
     * name $B$G;XDj$5$l$?%3%s%F%-%9%H$,$9$G$KB8:_$9$k>l9g$r=|$$$F(B bindContext() 
     * $B$HF1$8$G$"$k!#(B
     * $B%P%$%s%G%#%s%0$,$9$G$KB8:_$9$k>l9g$K$O!"?7$7$$%P%$%s%G%#%s%0$K(B
     * $BCV$-49$($i$l$k!#(B
     *
     * @param name $B%*%V%8%'%/%H$KIU$1$kL>A0$N%M!<%`%3%s%]!<%M%s%H(B
     * @param name_cxt $B4XO"IU$1$i$l$k(B NamingContext
     * @param force true$B$N>l9g!"ESCf$N%3%s%F%-%9%H$r6/@)E*$K%P%$%s%I$9$k(B
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindContext(const CosNaming::Name& name,
		       CosNaming::NamingContext_ptr name_cxt,
		       const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief NamingContext $B$r(B rebind $B$9$k(B
     *
     * name $B$G;XDj$5$l$?%3%s%F%-%9%H$,$9$G$KB8:_$9$k>l9g$r=|$$$F(B bindContext() 
     * $B$HF1$8$G$"$k!#(B
     * $B%P%$%s%G%#%s%0$,$9$G$KB8:_$9$k>l9g$K$O!"?7$7$$%P%$%s%G%#%s%0$K(B
     * $BCV$-49$($i$l$k!#(B
     *
     * @param name $B%*%V%8%'%/%H$KIU$1$kL>A0$NJ8;zNsI=8=(B
     * @param name_cxt $B4XO"IU$1$i$l$k(B NamingContext
     * @param force true$B$N>l9g!"ESCf$N%3%s%F%-%9%H$r6/@)E*$K%P%$%s%I$9$k(B
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindContext(const char* string_name,
		       CosNaming::NamingContext_ptr name_cxt,
		       const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);


    void rebindContextRecursive(CosNaming::NamingContext_ptr context,
				const CosNaming::Name& name,
				CosNaming::NamingContext_ptr name_cxt);

    /*!
     * @if jp
     *
     * @brief Object $B$r(B name $B$+$i2r7h$9$k(B
     *
     * name $B$K(B bind $B$5$l$F$$$k%*%V%8%'%/%H;2>H$rJV$9!#(B
     * $B%M!<%`%3%s%]!<%M%s%H(B <c_1, c_2, ... c_n> $B$O:F5"E*$K2r7h$5$l$k!#(B
     * 
     * CosNaming::resolve() $B$H$[$\F1Ey$NF/$-$r$9$k$,!">o$KM?$($i$l$?(B
     * $B%M!<%`%5!<%P$N%k!<%H%3%s%F%-%9%H$KBP$7$F(B resolve() $B$,8F$S=P$5$l$kE@$,(B
     * $B0[$J$k!#(B
     *
     * @param name $B2r7h$9$Y$-%*%V%8%'%/%H$NL>A0$N%M!<%`%3%s%]!<%M%s%H(B
     * @return $B2r7h$5$l$?%*%V%8%'%/%H;2>H(B
     *
     * @else
     *
     * @endif
     */
    CORBA::Object_ptr resolve(const CosNaming::Name& name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief Object $B$r(B name $B$+$i2r7h$9$k(B
     *
     * name $B$K(B bind $B$5$l$F$$$k%*%V%8%'%/%H;2>H$rJV$9!#(B
     * $B%M!<%`%3%s%]!<%M%s%H(B <c_1, c_2, ... c_n> $B$O:F5"E*$K2r7h$5$l$k!#(B
     * 
     * CosNaming::resolve() $B$H$[$\F1Ey$NF/$-$r$9$k$,!">o$KM?$($i$l$?(B
     * $B%M!<%`%5!<%P$N%k!<%H%3%s%F%-%9%H$KBP$7$F(B resolve() $B$,8F$S=P$5$l$kE@$,(B
     * $B0[$J$k!#(B
     *
     * @param name $B2r7h$9$Y$-%*%V%8%'%/%H$NL>A0$NJ8;zNsI=8=(B
     * @return $B2r7h$5$l$?%*%V%8%'%/%H;2>H(B
     *
     * @else
     *
     * @endif
     */
    CORBA::Object_ptr resolve(const char* string_name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief $B;XDj$5$l$?L>A0$N%*%V%8%'%/%H$N(B bind $B$r2r=|$9$k(B
     *
     * name $B$K(B bind $B$5$l$F$$$k%*%V%8%'%/%H;2>H$rJV$9!#(B
     * $B%M!<%`%3%s%]!<%M%s%H(B <c_1, c_2, ... c_n> $B$O:F5"E*$K2r7h$5$l$k!#(B
     * 
     * CosNaming::unbind() $B$H$[$\F1Ey$NF/$-$r$9$k$,!">o$KM?$($i$l$?(B
     * $B%M!<%`%5!<%P$N%k!<%H%3%s%F%-%9%H$KBP$7$F(B unbind() $B$,8F$S=P$5$l$kE@$,(B
     * $B0[$J$k!#(B
     *
     * @param name $B2r7h$9$Y$-%*%V%8%'%/%H$NL>A0$N%M!<%`%3%s%]!<%M%s%H(B
     * @return $B2r7h$5$l$?%*%V%8%'%/%H;2>H(B
     *
     * @else
     *
     * @endif
     */
    void unbind(const CosNaming::Name& name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief $B;XDj$5$l$?L>A0$N%*%V%8%'%/%H$N(B bind $B$r2r=|$9$k(B
     *
     * name $B$K(B bind $B$5$l$F$$$k%*%V%8%'%/%H;2>H$rJV$9!#(B
     * $B%M!<%`%3%s%]!<%M%s%H(B <c_1, c_2, ... c_n> $B$O:F5"E*$K2r7h$5$l$k!#(B
     * 
     * CosNaming::unbind() $B$H$[$\F1Ey$NF/$-$r$9$k$,!">o$KM?$($i$l$?(B
     * $B%M!<%`%5!<%P$N%k!<%H%3%s%F%-%9%H$KBP$7$F(B unbind() $B$,8F$S=P$5$l$kE@$,(B
     * $B0[$J$k!#(B
     *
     * @param name $B2r7h$9$Y$-%*%V%8%'%/%H$NL>A0$NJ8;zNsI=8=(B
     * @return $B2r7h$5$l$?%*%V%8%'%/%H;2>H(B
     *
     * @else
     *
     * @endif
     */
    void unbind(const char* string_name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief $B?7$7$$%3%s%F%-%9%H$r@8@.$9$k(B
     *
     * $BM?$($i$l$?%M!<%`%5!<%P>e$G@8@.$5$l$?(B NamingContext $B$rJV$9!#(B
     * $BJV$5$l$?(B NamingContext $B$O(B bind $B$5$l$F$$$J$$!#(B
     * 
     * @return $B@8@.$5$l$??7$7$$(B NamingContext
     *
     * @else
     *
     * @endif
     */
    CosNaming::NamingContext_ptr newContext();

    /*!
     * @if jp
     *
     * @brief $B?7$7$$%3%s%F%-%9%H$r(B bind $B$9$k(B
     *
     * $BM?$($i$l$?(B name $B$KBP$7$F?7$7$$%3%s%F%-%9%H$r%P%$%s%I$9$k!#(B
     * $B@8@.$5$l$?!!(BNamingContext $B$O%M!<%`%5!<%P>e$G@8@.$5$l$?$b$N$G$"$k!#(B
     * 
     * @param name NamingContext$B$KIU$1$kL>A0$N%M!<%`%3%s%]!<%M%s%H(B
     * @return $B@8@.$5$l$??7$7$$(B NamingContext
     *
     * @else
     *
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindNewContext(const CosNaming::Name& name, bool force = true)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief $B?7$7$$%3%s%F%-%9%H$r(B bind $B$9$k(B
     *
     * $BM?$($i$l$?(B name $B$KBP$7$F?7$7$$%3%s%F%-%9%H$r%P%$%s%I$9$k!#(B
     * $B@8@.$5$l$?!!(BNamingContext $B$O%M!<%`%5!<%P>e$G@8@.$5$l$?$b$N$G$"$k!#(B
     * 
     * @param name NamingContext$B$KIU$1$kL>A0$NJ8;zNsI=8=(B
     * @return $B@8@.$5$l$??7$7$$(B NamingContext
     *
     * @else
     *
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindNewContext(const char* string_name, bool force = true)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief NamingContext $B$rHs%"%/%F%#%V2=$9$k(B
     *
     * context $B$G;XDj$5$l$?(B NamingContext $B$rHs%"%/%F%#%V2=$9$k!#(B
     * context $B$KB>$N%3%s%F%-%9%H$,%P%$%s%I$5$l$F$$$k>l9g$O(B NotEmpty $BNc30$,(B
     * $BH/@8$9$k!#(B
     * 
     * @param context $BHs%"%/%F%#%V2=$9$k(B NamingContext
     *
     * @else
     *
     * @brief Destroy the naming context
     *
     * Delete the specified naming context.
     * any bindings should be <unbind> in which the given context is bound to
     * some names before invoking <destroy> operation on it. 
     *
     * @param context NamingContext which is destroied.
     *     
     * @endif
     */
    void destroy(CosNaming::NamingContext_ptr context)
      throw(NotEmpty);


    /*!
     * @if jp
     * @brief NamingContext $B$r:F5"E*$K2<$C$FHs%"%/%F%#%V2=$9$k(B
     * @else
     * @brief Destroy the naming context recursively
     * @endif
     */
    void destroyRecursive(CosNaming::NamingContext_ptr context)
      throw(NotEmpty, NotFound, CannotProceed, InvalidName);


    /*!
     * @if jp
     * @brief $B$9$Y$F$N(B Binding $B$r:o=|$9$k(B
     * @else
     * @brief Destroy all binding
     * @endif
     */
    void clearAll();


    /*!
     * @if jp
     * @brief $BM?$($i$l$?(B NamingContext $B$N(B Binding $B$r<hF@$9$k(B
     * @else
     * @brief Get Binding on the NamingContextDestroy all binding
     * @endif
     */
    void list(CosNaming::NamingContext_ptr name_cxt,
	      unsigned long how_many,
	      CosNaming::BindingList_var& bl,
	      CosNaming::BindingIterator_var& bi);


    //============================================================
    // interface of NamingContextExt
    //============================================================
    /*!
     * @if jp
     * @brief $BM?$($i$l$?(B NameComponent $B$NJ8;zNsI=8=$rJV$9(B
     * @else
     * @brief Get string representation of given NameComponent
     * @endif
     */
    char* toString(const CosNaming::Name& name)
      throw(InvalidName);
    

    /*!
     * @if jp
     * @brief $BM?$($i$l$?J8;zNsI=8=$r(B NameComponent $B$KJ,2r$9$k(B
     * @else
     * @brief Get NameComponent from gien string name representation
     * @endif
     */
    CosNaming::Name toName(const char* string_name)
      throw(InvalidName);


    /*!
     * @if jp
     * @brief $BM?$($i$l$?(B addre $B$H(B string_name $B$+$i(B URL$BI=8=$r<hF@$9$k(B
     * @else
     * @brief Get URL representation from given addr and string_name
     * @endif
     */
    char* toUrl(char* addr, char* string_name)
      throw(InvalidAddress, InvalidName);


    /*!
     * @if jp
     * @brief $BM?$($i$l$?J8;zNsI=8=$r(B resolve $B$7%*%V%8%'%/%H$rJV$9(B
     * @else
     * @brief Resolve from name of string representation and get object 
     * @endif
     */
    CORBA::Object_ptr resolveStr(const char* string_name)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);


    //============================================================
    // Find functions
    //============================================================

    //    ObjectList find(const char* name, const char* kind);
    //    ObjectList findById(const char* name, const char* kind);
    //    ObjectList findByKind(const char* name, const char* kind);


    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    const char* getNameServer();
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::NamingContext_ptr getRootContext();

    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    bool isNamingContext(CORBA::Object_ptr obj);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    bool isNamingContext(const CosNaming::Name& name);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    bool isNamingContext(const char* string_name);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::Name subName(const CosNaming::Name& name,
			    long begin,
			    long end = -1);

    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CORBA::Object_ptr bindOrResolve(CosNaming::NamingContext_ptr context,
				    const CosNaming::Name& name,
				    CORBA::Object_ptr obj);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindOrResolveContext(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name,
			 CosNaming::NamingContext_ptr new_context);

    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindOrResolveContext(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name);


  protected:
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CORBA::ULong getNameLength(const CosNaming::Name& name);

    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    void nameToString(const CosNaming::Name& name, char* string_name,
		      unsigned long slen);
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    unsigned int split(const std::string& input,
		       const std::string& delimiter,
		       std::vector<std::string>& results);
    
    CORBA::ORB_var m_varORB;
    std::string m_nameServer;
    CosNaming::NamingContextExt_var m_rootContext;

  private:
    CORBA::ULong m_blLength;
    
  };

}; // end of namespace RTM

#endif // end of __RtcNaming_h__
