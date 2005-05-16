// -*- C++ -*-
/*!
 * @file RtcNaming.h
 * @brief naming Service helper class
 * @date $Date: 2005-05-16 06:29:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcNaming.h,v 1.2 2005-05-16 06:29:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */


#ifndef RtcNaming_h
#define RtcNaming_h

// CORBA header include
#include "rtm/idl/RTMBaseStub.h"
#include "rtm/idl/RTMBaseSkel.h"
#include "rtm/RtcBase.h"

// STL includes
#include <map>
#include <string>
#include <vector>

#define HOST_CTXT_LEVEL 1
#define MANAGER_CTXT_LEVEL 2
#define MANAGER_LEVEL 3
#define CATEGORY_CTXT_LEVEL 3
#define MODULE_CTXT_LEVEL 4
#define COMPONENT_LEVEL 5

namespace RTM
{
  using namespace std;
  
  typedef std::vector<CosNaming::NamingContextExt_var> ContextList;
  typedef std::vector<CORBA::Object_ptr> ObjectList;


  /*!
   * @if jp
   *
   * @class RtcNaming
   *
   * @brief CORBA Naming Service ���������إ�ѡ����饹
   *
   * @else
   *
   * @class RtcNaming
   *
   * @brief CORBA Naming Service access helper class
   *
   * @endif
   */
  class EXPORTS RtcNaming
  {
  public:
	/*!
	 * @if jp
	 * @brief RtcNaming ���饹���󥹥ȥ饯��
	 *
	 * @else
	 *
	 * @brief A constructor of RtcNaming class.
	 *
	 * @endif
	 */
    RtcNaming() : m_bindListNum(100) {};
	
	/*!
	 * @if jp
	 * @brief RtcNaming ���饹���󥹥ȥ饯��
	 *
	 * @else
	 *
	 * @brief A constructor of RtcNaming class.
	 *
	 * @endif
	 */
    RtcNaming(CORBA::ORB_ptr orb) : m_bindListNum(100) {initNaming(orb);};
	
	/*!
	 * @if jp
	 * @brief RtcNaming ���饹�ǥ��ȥ饯��
	 *
	 * @else
	 *
	 * @brief A destructor of RtcNaming class.
	 *
	 * @endif
	 */
	~RtcNaming();
	
	
	/*!
	 * @if jp
	 * @brief RtcNaming ���饹�ǥ��ȥ饯��
	 *
	 * @param orb ORB �ؤΥݥ���
	 *
	 * @else
	 *
	 * @brief Initialize RtcNaming object
	 *
	 * @param orb pointer tod ORB
	 *
	 * @endif
	 */
    bool initNaming(const CORBA::ORB_ptr orb);
	
	
    //============================================================
    // << Create and Bind Methods >>
    //============================================================
	
	
	/*!
	 * @if jp
	 * @brief �͡��ߥ󥰥���ƥ����Ȥ�����
	 *
	 * Ϳ����줿�͡��ߥ󥰥���ƥ����Ⱦ�� id,kind �Υ���ƥ����Ȥ�����
	 * 
     * @param context ����ƥ����Ȥ���������ƥ͡��ߥ󥰥���ƥ�����
     * @param id ����ƥ����� ID
     * @param kind ����ƥ����� KIND
	 *
	 * @else
	 *
	 * @brief Create naming context
	 *
     * Create a naming context using Context_var, id and kind
	 *
     * @param context Naming context to be created new context
     * @param id context ID
     * @param kind context KIND
	 *
	 * @endif
	 */
    CosNaming::NamingContextExt_var
    createContext(CosNaming::NamingContextExt_var context,
				  const std::string& id, const std::string& kind);
	
	
	/*!
	 * @if jp
	 * @brief �ۥ��ȥ���ƥ����Ȥ�����
	 *
	 * �ۥ��ȥ���ƥ����ȥ�٥�˥ۥ���̾�Υ���ƥ����Ȥ���������
	 * 
     * @param id ����ƥ�����̾�Ȥ���Ϳ����ۥ���̾
	 *
	 * @else
	 *
	 * @brief Create host context
	 *
     * Create host context on the default naming service.
	 *
     * @param id host name as a context id 
	 *
	 * @endif
	 */
    bool createHostContext(const std::string& id);
	
	
	/*!
	 * @if jp
	 * @brief �ޥ͡����㥳��ƥ����Ȥ�����
	 *
	 * �ޥ͡����㥳��ƥ����ȥ�٥�˥ޥ͡�����̾�Υ���ƥ����Ȥ���������
	 * 
     * @param id ����ƥ�����̾�Ȥ���Ϳ����ޥ͡�����̾
	 *
	 * @else
	 *
	 * @brief Create manager context
	 *
     * Create manager context on the default naming service.
	 *
     * @param id manager name as a context id 
	 *
	 * @endif
	 */
    bool createManagerContext(const std::string& id);
	
	
	/*!
	 * @if jp
	 * @brief ���ƥ��ꥳ��ƥ����Ȥ�����
	 *
	 * ���ƥ��ꥳ��ƥ����ȥ�٥�˥ޥ͡�����̾�Υ���ƥ����Ȥ���������
	 * 
     * @param id ����ƥ�����̾�Ȥ���Ϳ���륫�ƥ���̾
	 *
	 * @else
	 *
	 * @brief Create category context
	 *
     * Create category context on the default naming service.
	 *
     * @param id category name as a context id 
	 *
	 * @endif
	 */
    bool createCategoryContext(const std::string& category);
	
	
	/*!
	 * @if jp
	 * @brief �⥸�塼�륳��ƥ����Ȥ�����
	 *
	 * �⥸�塼�륳��ƥ����ȥ�٥�˥ޥ͡�����̾�Υ���ƥ����Ȥ���������
	 * 
     * @param module ����ƥ�����̾�Ȥ���Ϳ����⥸�塼��̾
     * @param category �⥸�塼�륳��ƥ����Ȥ�������륫�ƥ���̾
	 *
	 * @else
	 *
	 * @brief Create module context
	 *
     * Create module context on the default naming service.
	 *
     * @param module module name as a context id 
     * @param category category name on which module context is created
	 *
	 * @endif
	 */
    bool createModuleContext(const std::string& module,
							 const std::string& category);
	
	
	/*!
	 * @if jp
	 * @brief ���֥������ȤΥХ����
	 *
	 * ���֥������Ȥ���ꤷ������ƥ����Ȳ��˥Х����
	 * 
     * @param context ���֥������Ȥ�Х���ɤ��륳��ƥ�����
     * @param id ���֥������� ID
     * @param kind ���֥������� KIND
     * @param obj �Х���ɤ��륪�֥������ȤΥ��֥������ȥ�ե����
	 *
	 * @else
	 *
	 * @brief Bind object to a context
	 *
     * Bind object to specified naming context
	 *
     * @param context A context to be bound the object
     * @param id object ID
     * @param kind object KIND
     * @param obj Object pointer to be bound
	 *
	 * @endif
	 */
    bool bindObject(CosNaming::NamingContextExt_var context,
					const std::string& id, const std::string& kind,
					CORBA::Object_ptr obj);

	/*!
	 * @if jp
	 * @brief ���֥������Ȥ�ե�ѥ�����ǥХ����
	 *
	 * ���֥������Ȥ����ե�ѥ��˽��äƥХ���ɤ��롣
	 * 
     * @param path ���֥������Ȥ�Х���ɤ���͡��ߥ󥰥ĥ꡼�Υե�ѥ�
     * @param obj �Х���ɤ��륪�֥������ȤΥ��֥������ȥ�ե����
	 *
	 * @else
	 *
	 * @brief Bind object to a context specified full path string
	 *
     * Bind object to specified full path string.
	 *
     * @param path A full path string to be bound a object.
     * @param obj Object reference to be bound
	 *
	 * @endif
	 */
	bool bindObjectByFullPath(const std::string& path,
							  CORBA::Object_ptr obj);
	
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȤΥХ����
	 *
	 * ���֥������Ȥ���ꤷ������ƥ����Ȳ��˥Х����
	 * 
     * @param id ����ݡ��ͥ�Ȥ� ID
     * @param category ����ݡ��ͥ�ȤΥ��ƥ���
     * @param obj ����ݡ��ͥ�ȤΥ��֥������ȥ�ե����
	 *
	 * @else
	 *
	 * @brief Bind component to a context
	 *
     * Bind object to specified naming context
	 *
     * @param id object ID
     * @param category A category bind to the obobject
     * @param obj Component object pointer to be bound
	 *
	 * @endif
	 */
    bool bindComponent(const std::string& component, const std::string& module,
					   const std::string& category, CORBA::Object_ptr obj);
	
	/*!
	 * @if jp
	 * @brief �ޥ͡�����ΥХ����
	 *
	 * �ޥ͡��������ꤷ������ƥ����Ȳ��˥Х����
	 * 
     * @param id �ޥ͡�����̾
     * @param obj �ޥ͡�����Υ��֥������ȥ�ե����
	 *
	 * @else
	 *
	 * @brief Bind manager to a context
	 *
     * Bind manager object to specified naming context
	 *
     * @param id Manager's name as a object id
     * @param obj Manager's object pointer
	 *
	 * @endif
	 */
    bool bindManager(const std::string& id, CORBA::Object_ptr obj);
	
	
    //============================================================
    // << Destroy and Unbind methods >>
    //============================================================
	
	
	/*!
	 * @if jp
	 * @brief ��ʬ�Υۥ��ȥ���ƥ����Ȥκ��
	 *
	 * @else
	 * @brief Destroy host context
	 *
	 * @endif
	 */
    bool destroyHostContext();
	
	/*!
	 * @if jp
	 * @brief ��ʬ�Υޥ͡����㥳��ƥ����Ȥκ��
	 *
	 * @else
	 * @brief Destroy manager context
	 *
	 * @endif
	 */
    bool destroyManagerContext();
	
	/*!
	 * @if jp
	 * @brief ���ƥ��ꥳ��ƥ����Ȥκ��
	 *
	 * @param id ���ƥ���̾
	 *
	 * @else
	 * @brief Destroy manager context
	 *
	 * @param id Category name
	 *
	 * @endif
	 */
    bool destroyCategoryContext(const std::string& id);
	
	
	/*!
	 * @if jp
	 * @brief �⥸�塼�륳��ƥ����Ȥκ��
	 *
	 * @param module �⥸�塼��̾
	 * @param category ���ƥ���̾
	 *
	 * @else
	 * @brief Destroy manager context
	 *
	 * @param module Module name
	 * @param category Category name
	 *
	 * @endif
	 */
    bool destroyModuleContext(const std::string& module,
							  const std::string& category);
	
	
	/*!
	 * @if jp
	 * @brief ���֥������ȤΥ���Х����
	 *
	 * ���ꤷ������ƥ����Ȳ��Υ��֥������Ȥ򥢥�Х����
	 * 
     * @param context ���֥������Ȥ�Х���ɤ��륳��ƥ�����
     * @param id ���֥������� ID
     * @param kind ���֥������� KIND
	 *
	 * @else
	 *
	 * @brief Unbind object to a context
	 *
     * Unbind object to specified naming context
	 *
     * @param context A context to be unbound the object
     * @param id object ID
     * @param kind object KIND
	 *
	 * @endif
	 */
    bool unbindObject(CosNaming::NamingContextExt_var context,
					  const std::string& id, const std::string& kind);



	/*!
	 * @if jp
	 * @brief ���֥������Ȥ�ե�ѥ�����ǥ���Х����
	 *
	 * ���֥������Ȥ����ե�ѥ��˽��äƥ���Х���ɤ��롣
	 * 
     * @param path ����Х���ɤ��륪�֥������ȤΥե�ѥ�
	 *
	 * @else
	 *
	 * @brief Unbind object to a context specified full path string
	 *
     * Unbind object to specified full path string.
	 *
     * @param path A full path string to be bound a object.
	 *
	 * @endif
	 */
	bool unbindObjectByFullPath(const std::string& path);


	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ��֥������Ȥ򥢥�Х����
	 *
	 * ����RtcNaming���饹�ǥХ���ɤ��줿��󥰥͡���Υ��֥������Ȥ�
	 * ����Х���ɤ��롣
	 * 
     * @param category ����Х���ɤ��륪�֥������ȤΥ��ƥ���̾
     * @param module ����Х���ɤ��륪�֥������ȤΥ⥸�塼��̾
     * @param instance ����Х���ɤ��륪�֥������ȤΥ��󥹥���̾
	 *
	 * @else
	 *
	 * @brief Unbind component object
	 *
     * Unbind object which was bound this RtcNaming object.
	 *
     * @param category Category name of the object to be unbound.
     * @param module Module name of the object to be unbound.
     * @param instance Instance name of the object to be unbound.
	 *
	 * @endif
	 */
	bool unbindLocalComponent(const std::string category,
							  const std::string module,
							  const std::string instance);
	


    //============================================================
    // << Find methods >>
    //============================================================
	
	/*!
	 * @if jp
	 * @brief �ۥ��ȥ���ƥ����Ȥθ���
	 *
	 * @param id_seq ��������ID��
	 * @param context ����ƥ������� (�����)
	 *
	 * @else
	 * @brief Find host context
	 *
	 * @param id_seq ID sequence to be find
	 * @param context context sequence (return value)	
	 *
	 * @endif
	 */
    bool findHostContext(const std::string& id_seq, ContextList& context);
	
	
	/*!
	 * @if jp
	 * @brief ���ƥ��ꥳ��ƥ����Ȥθ���
	 *
	 * @param id_seq ��������ID��
	 * @param context ����ƥ������� (�����)
	 *
	 * @else
	 * @brief Find category context
	 *
	 * @param id_seq ID sequence to be find
	 * @param context context sequence (return value)	
	 *
	 * @endif
	 */
    bool findCategoryContext(const std::string& id_seq, ContextList& context);
	
	
	/*!
	 * @if jp
	 * @brief �⥸�塼�륳��ƥ����Ȥθ���
	 *
	 * @param id_seq ��������ID��
	 * @param context ����ƥ������� (�����)
	 *
	 * @else
	 * @brief Find module context
	 *
	 * @param id_seq ID sequence to be find
	 * @param context context sequence (return value)	
	 *
	 * @endif
	 */
    bool findModuleContext(const std::string& id_seq, ContextList& context);
	
	
	/*!
	 * @if jp
	 * @brief �ޥ͡����㥳��ƥ����Ȥθ���
	 *
	 * @param id_seq ��������ID��
	 * @param context ����ƥ������� (�����)
	 *
	 * @else
	 * @brief Find manager context
	 *
	 * @param id_seq ID sequence to be find
	 * @param context context sequence (return value)	
	 *
	 * @endif
	 */
    bool findManagerContext(const std::string& id_seq, ContextList& context);
	
	
	/*!
	 * @if jp
	 * @brief �ޥ͡����㥪�֥������ȥ�ե���󥹤θ���������
	 *
	 * @param id_seq ��������ID��
	 * @param object ���֥������ȥ�ե������ (�����)
	 *
	 * @else
	 * @brief Find and get manager object reference
	 *
	 * @param id_seq ID sequence to be find
	 * @param object objecte reference list (return value)	
	 *
	 * @endif
	 */
    bool findManager(std::string& id, ObjectList& objects);
	
	
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ��֥������ȥ�ե���󥹤θ���������
	 *
	 * @param id_seq ��������ID��
	 * @param object ���֥������ȥ�ե������ (�����)
	 *
	 * @else
	 * @brief Find and get component object reference
	 *
	 * @param id_seq ID sequence to be find
	 * @param object objecte reference list (return value)	
	 *
	 * @endif
	 */
    bool findComponents(const std::string& id_seq, ObjectList& objects);
	
	
  protected:
	/*!
	 * @if jp
	 * @brief �͡��ߥ󥰥���ƥ����ȤκƵ�Ū���
	 *
	 * @param context ����򳫻Ϥ��륳��ƥ�����
	 *
	 * @else
	 * @brief Destroy naming context recursive
	 *
	 * @param context Starting point naming context to be deleted.
	 *
	 * @endif
	 */
    bool destroyRecursive(CosNaming::NamingContextExt_var context);
	
	
	/*!
	 * @if jp
	 * @brief ���֥������ȥ�ե���󥹤�Ƶ�Ū�˼���
	 *
	 * @param context �����򳫻Ϥ��륳��ƥ�����
	 * @param path �����ѥ�
	 * @param obj ���֥������ȥ�ե������ (�����)
	 *
	 * @else
	 * @brief Find object reference recursive
	 *
	 * @param context Starting point naming context 
	 * @param path Search path name
	 * @param obj Object reference list (return value)
	 *
	 * @endif
	 */
    void findObjectsRecursive(CosNaming::NamingContextExt_ptr context,
							  const std::string& path, ObjectList& obj);
	
	/*!
	 * @if jp
	 * @brief �͡��ߥ󥰥���ƥ����Ȥ�Ƶ�Ū�˼���
	 *
	 * @param context �����򳫻Ϥ��륳��ƥ�����
	 * @param path �����ѥ�
	 * @param context_list ����ƥ������� (�����)
	 *
	 * @else
	 * @brief Find naming context recursive
	 *
	 * @param context Starting point naming context 
	 * @param path Search path name
	 * @param context_list Naming context list (return value)
	 *
	 * @endif
	 */
    void findContextRecursive(CosNaming::NamingContextExt_var context,
							  const std::string& path, ContextList& context_list);
	
	
	/*!
	 * @if jp
	 * @brief ����ƥ����ȡ����֥������Ȥ�Ƶ�Ū�˥Х����
	 *
	 * @param context �Х���ɤ򳫻Ϥ��륳��ƥ�����
	 * @param path �����ѥ�
	 * @param obj ���֥������ȥ�ե����
	 *
	 * @else
	 * @brief Bind context/object recursive
	 *
	 * @param context Starting point naming context 
	 * @param path Binding path name
	 * @param obj Object reference to be bound
	 *
	 * @endif
	 */
	void bindObjectRecursive(CosNaming::NamingContextExt_var context,
							 const std::string& path,
							 CORBA::Object_ptr obj);
	
	
  private:
	/*!
	 * @if jp
	 * @brief ʸ�����ʬ��
	 * @else
	 * @brief Strig split function
	 * @endif
	 */
    int split(const std::string& input, const std::string& delimiter,
			  std::vector<std::string>& results);
	
	/*!
	 * @if jp
	 * @brief Ϳ����줿ʸ�����ե�ѥ��ˤ���
	 * @else
	 * @brief Convert given string to full path string
	 *
	 * If given path is "hoge/munya" and level is 5, it is converted to 
	 * "*./*./*./hoge/munya".
	 *
	 * @param path path which have to converted to full path
	 * @param level compensation level
	 *
	 * @endif
	 */
    std::string makeFullPath(std::string path, int level);
	
	/*!
	 * @if jp
	 * @brief ���ߤΥΡ��ɤ��ڤ�Ф�
	 *
	 * @param path �ѥ�
	 * @param node �ڤ�Ф��줿�Ρ���̾ (�����)
	 * @param remain �Ĥ�Υѥ� (�����)
	 *
	 * @else
	 * @brief Convert given string to full path string
	 *
	 * @param path Given path
	 * @param node Picked up path node name (return value)
	 * @param remain Remain path string (return value)
	 *
	 * @endif
	 */
    bool pickupNode(const std::string& path, std::string& node, std::string& remain);
	
	/*!
	 * @if jp
	 * @brief Ϳ����줿ʸ����� ID �� KIND ��ʬ�䤹��
	 * Kind �����ξ�� ".*" ����������롣
	 *
	 * @param node �Ρ���̾
	 * @param id ID (�����)
	 * @param kind KIND (�����)
	 *
	 * @else
	 * @brief Convert given string to full path string
	 *
	 * @param node Node name
	 * @param id ID (return value)
	 * @param kind KIND (return value)
	 *
	 * @endif
	 */
    void nodeToIdKindAny(const std::string& node,
					  std::string& id, std::string& kind);

	/*!
	 * @if jp
	 * @brief Ϳ����줿ʸ����� ID �� KIND ��ʬ�䤹��
	 *
	 * @param node �Ρ���̾
	 * @param id ID (�����)
	 * @param kind KIND (�����)
	 *
	 * @else
	 * @brief Convert given string to full path string
	 *
	 * @param node Node name
	 * @param id ID (return value)
	 * @param kind KIND (return value)
	 *
	 * @endif
	 */
    void nodeToIdKind(const std::string& node,
					  std::string& id, std::string& kind);
	
  private:
	
	/*!
	 * @if jp
	 * @brief �͡��ߥ󥰥����ӥ��Υ��֥������ȥ�ե����
	 * @else
	 * @brief Object reference of Naming Service
	 * @endif
	 */
    CORBA::Object_var m_nameRef;
	
	/*!
	 * @if jp
	 * @brief �롼�ȥ���ƥ�����
	 * @else
	 * @brief Root naming context
	 * @endif
	 */
    CosNaming::NamingContextExt_var m_rootContext;
	
	/*!
	 * @if jp
	 * @brief �ۥ��ȥ���ƥ�����
	 * @else
	 * @brief Host naming context
	 * @endif
	 */
    CosNaming::NamingContextExt_var m_hostContext;
	std::string m_hostName;

	/*!
	 * @if jp
	 * @brief �ޥ͡����㥳��ƥ�����
	 * @else
	 * @brief Manager naming context
	 * @endif
	 */
    CosNaming::NamingContextExt_var m_mngrContext;
	std::string m_mngrName;

	/*!
	 * @if jp
	 * @brief ���ƥ��ꥳ��ƥ����ȥޥå�
	 * @else
	 * @brief Category naming context map
	 * @endif
	 */
    std::map<std::string, CosNaming::NamingContextExt_var> m_cateContext;
	
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ���ƥ����ȥޥå�
	 * @else
	 * @brief Category naming context map
	 * @endif
	 */
    std::map<std::string, std::map<std::string, CosNaming::NamingContextExt_var> > m_compContext;
	
	/*!
	 * @if jp
	 * @brief ��������͡��ߥ󥰥���ƥ����Ȥκ����
	 * @else
	 * @brief maximum number of naming context to get at once
	 * @endif
	 */
    int m_bindListNum;
	
	/*!
	 * @if jp
	 * @brief ���֥������ȥꥹ��
	 * @else
	 * @brief Object reference list
	 * @endif
	 */
    std::vector<CORBA::Object_ptr> m_vObjects;
	
  };
  
}; // end of namespace RTM

#endif // end of __RtcNaming_h__
