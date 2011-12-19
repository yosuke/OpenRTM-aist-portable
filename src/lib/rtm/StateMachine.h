// -*- C++ -*-
/*!
 * @file StateMachine.h
 * @brief State machine template class
 * @date $Date: 2007-09-20 11:21:12 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: StateMachine.h 2015 2010-12-29 11:33:33Z n-ando $
 *
 */

#ifndef RTC_STATEMACHINE_H
#define RTC_STATEMACHINE_H

#include <rtm/RTC.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>

namespace RTC_Utils
{
  /*!
   * @if jp
   * @class StateHolder
   * @brief �����ݻ��ѥ��饹
   * 
   * ���֤��ݻ����뤿��Υۥ�������饹��
   * ���ߤξ��֤ȡ��������ξ��֡�����ͽ��ξ��֤��ݻ����롣
   *
   * @param State �ݻ�������֤η�
   *
   * @since 0.4.0
   *
   * @else
   * @class StateHolder
   * @brief State holder class
   * 
   * This is a holder class to hold states.
   * Hold current state, the previous state and the
   * state to be expected to transfer.
   *
   * @param State Type of state for holding
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class State>
  struct StateHolder
  {
    State curr;
    State prev;
    State next;
  };
  
  /*!
   * @if jp
   *
   * @class StateMachine
   *
   * @brief ���֥ޥ��󥯥饹
   *
   * StateMachine ���饹�Ͼ��֥ޥ����¸����륯�饹�Ǥ��롣
   *
   * ��: ActiveObject�Ͼ��֥ޥ������ĥ����ƥ��֥��֥������ȤǤ���Ȥ��롣
   * ���֤�3���� INACTIVE, ACTIVE, ERROR �����ꡢ�ƾ��֤Ǥ�Entry��Exitư���
   * ����������Ȥ���ȡ��ʲ��Τ褦�˼¸�����롣
   * <pre>
   * class ActiveObject 
   * {  
   * public: 
   *   enum MyState { INACTIVE, ACTIVE, ERROR }; 
   *   typedef States<MyState> MyStates; 
   *  
   *   ActiveObject() 
   *     : m_sm(3) 
   *   { 
   *     m_sm.setNOP(&ActiveObject::nullAction); 
   *     m_sm.setListener(this); 
   *  
   *     m_sm.setExitAction(INACTIVE, &ActiveObject::inactiveExit); 
   *       : 
   *     m_sm.setPostDoAction(ERROR, &ActiveObject::errorPostDo); 
   *     m_sm.setTransitionAction(&ActiveObject:transition); 
   *   }; 
   *  
   *   bool nullAction(MyStates st) {}; 
   *   bool inactiveExit(MyStates st) {}; 
   *     : 
   *   bool errorPostDo(MyStates st) {}; 
   *   bool transition(MyStates st) {}; 
   *  
   * private: 
   *   StateMachine<MyState, bool, ActiveObject> m_sm; 
   * }; 
   * </pre>
   * ���֤�������������饹�ϰʲ��ξ����������褦�˼������ʤ���Фʤ�ʤ���
   * <ol>
   * <li> enum �Ǿ��֤����
   * <li> StateMachine �Υƥ�ץ졼�Ȱ����ϡ�<br>
   *   <���֤η�(MyState), �ꥹ�ʡ����֥�������, ���֥ۥ������������Хå��ؿ�>
   * <li> StateMachine �Υ��󥹥ȥ饯�������Ͼ��֤ο�
   * <li> �ʲ��Υ��������ؿ���(Return _function_name_(States)) �δؿ��Ȥ�������
   * <ol>
   *  <li> ���⤷�ʤ��ؿ���ɬ���������setNOP ��Ϳ���ʤ���Фʤ�ʤ�
   *  <li> �ƾ������, set(Entry|PreDo|Do|PostDo|Exit)Action �ǥ�������������
   *  <li> �������ܻ��Υ��������� setTransitionAction() �����ꡣ
   * </ol>
   * <li> ���ܻ��Υ��������ϡ�Ϳ����줿���߾��֡������֡������֤򸵤ˡ�
   *   �桼�����������ʤ���Фʤ�ʤ���
   * <li> ���֤��ѹ��� goTo() �ǡ����֤Υ����å��� isIn(state) �ǹԤ���
   * <li> goTo()�ϼ����֤���Ū�˥��åȤ���ؿ��Ǥ��ꡢ���ܤβ��ݤϡ�
   *   �桼�������߾��֤������Ƚ�Ǥ�����å���������ʤ���Фʤ�ʤ���
   * </ol>
   *
   * ���Υ��饹�ϡ���Ĥξ��֤��Ф��ơ�
   * <ul>
   * <li> Entry action
   * <li> PreDo action
   * <li> Do action
   * <li> PostDo action
   * <li> Exit action
   * </ul>
   * 5�ĤΥ��������������뤳�Ȥ��Ǥ��롣
   * Transition action �Ϥ�������ִ����ܤǸƤӽФ���륢�������ǡ�
   * ���ο����񤤤ϥ桼����������ʤ���Фʤ�ʤ���
   * 
   * ���Υ��饹�ϰʲ��Τ褦�ʥ����ߥ󥰤ǳƥ�������󤬼¹Ԥ���롣
   *
   * <ul>
   * <li> ���֤��ѹ�����(A->B)���֤����ܤ����� <br>
   * (A:Exit)->|(���ֹ���:A->B)->(B:Entry)->(B:PreDo)->(B:Do)->(B:PostDo)
   *
   * <li> ���֤��ѹ����줺��B���֤�ݻ������� (|�ϥ��ƥåפζ��ڤ��ɽ��)<br>
   * (B(n-1):PostDo)->|(B(n):PreDo)->(B(n):Do)->(B(n):PostDo)->|(B(n+1):PreDo)<br>
   * PreDo, Do, PostDo �������֤��¹Ԥ���롣
   *
   * <li> �������ܤ����� <br>
   * (B(n-1):PostDo)->(B(n-1):Exit)->|(B(n):Entry)->(B(n):PreDo) <br>
   * ��ö Exit ���ƤФ줿�塢Entry ���¹Ԥ��졢�ʹߤ������Ʊ��ư��򤹤롣
   * </ul>
   *
   * @param State ���֤η�
   * @param Listener ����������ѥꥹ�ʡ����֥�������
   * @param States ���֥ۥ����
   * @param Callback ����������ѥ�����Хå��ؿ�
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class StateMachine
   *
   * @brief State machine class
   *
   * StateMachine class is a class to realize a state machine.
   *
   * Example: ActiveObject assumes to be an active object that has 
   * the state machine.
   * There are three states such as INACTIVE, ACTIVE and ERROR state, 
   * and if you want to define Entry or Exit action, this class will realize
   * as follows:
   * <pre>
   * class ActiveObject 
   * {  
   * public: 
   *   enum MyState { INACTIVE, ACTIVE, ERROR }; 
   *   typedef States<MyState> MyStates; 
   *  
   *   ActiveObject() 
   *     : m_sm(3) 
   *   { 
   *     m_sm.setNOP(&ActiveObject::nullAction); 
   *     m_sm.setListener(this); 
   *  
   *     m_sm.setExitAction(INACTIVE, &ActiveObject::inactiveExit); 
   *       : 
   *     m_sm.setPostDoAction(ERROR, &ActiveObject::errorPostDo); 
   *     m_sm.setTransitionAction(&ActiveObject:transition); 
   *   }; 
   *  
   *   bool nullAction(MyStates st) {}; 
   *   bool inactiveExit(MyStates st) {}; 
   *     : 
   *   bool errorPostDo(MyStates st) {}; 
   *   bool transition(MyStates st) {}; 
   *  
   * private: 
   *   StateMachine<MyState, bool, ActiveObject> m_sm; 
   * }; 
   * </pre>
   * If you want to give a class to some states, you must implement the class to 
   * satisfy the following conditions:
   * <ol>
   * <li> You must define states by enum.
   * <li> Template arguments of StateMachine must be
   *   <type of state(MyState), listener object, state holder��callback function>
   * <li> Constructor arguments of StateMachine must be the number of the states.
   * <li> You must set the following action functions as a function of
   *      (Return _function_name_(States))
   * <ol>
   *  <li> You must define a function that does not do anything and give with 
   *       setNOP.
   *  <li> You must set actions to each state 
   *       by set(Entry|PreDo|Do|PostDo|Exit)Action.
   *  <li> You should set actions at the state transition by setTransitionAction().
   * </ol>
   * <li> You must implement action at the transition based on given states, such
   *  as current state, next state and previous state.
   * <li> You should change states by goTo() and check the state by isIn(state).
   * <li> goTo() is a function that sets next state forcibly, therefore,
   *      to determine the next state, you must get current state and 
   *      implement that logic.
   * </ol>
   *
   * In this class, you can define the following five actions for one state:
   * <ul>
   * <li> Entry action
   * <li> PreDo action
   * <li> Do action
   * <li> PostDo action
   * <li> Exit action
   * </ul>
   * Transition action is an action invoked at the transition between any states,
   * and you must define its behavior.
   * 
   * This class executes each action according to the following timing.
   *
   * <ul>
   * <li> If the state is changed and transits(A->B) state,<br>
   * (A:Exit)->|(state update:A->B)->(B:Entry)->(B:PreDo)->(B:Do)->(B:PostDo)
   *
   * <li> If the state is not changed and remains B state, (| shows a step's break)
   * (B(n-1):PostDo)->|(B(n):PreDo)->(B(n):Do)->(B(n):PostDo)->|(B(n+1):PreDo)
   * PreDo, Do and PostDo are executed over and over again.
   *
   * <li> If the state transits to itself<br>
   * (B(n-1):PostDo)->(B(n-1):Exit)->|(B(n):Entry)->(B(n):PreDo) <br>
   * Once Exit is invoked, Entry is executed, and then the same operation described
   * above will be done from here on.
   * </ul>
   *
   * @param State Type of the state
   * @param Listener Listener object for action
   * @param States State holder
   * @param Callback Callback function for action
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class State,
	    class Listener,
	    class States = StateHolder<State>, 
	    class Callback = void (Listener::*)(const States& states)
	    >
  class StateMachine
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param num_of_state ���ơ��ȥޥ�����ξ��ֿ�
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param num_of_state Number of states in the state machine
     *
     * @endif
     */
    StateMachine(int num_of_state)
      : m_num(num_of_state),
	m_entry (new Callback[m_num]),
	m_predo (new Callback[m_num]),
	m_do    (new Callback[m_num]),
	m_postdo(new Callback[m_num]),
	m_exit  (new Callback[m_num])
    {
      setNullFunc(m_entry,  NULL);
      setNullFunc(m_do,     NULL);
      setNullFunc(m_exit,   NULL);
      setNullFunc(m_predo,  NULL);
      setNullFunc(m_postdo, NULL);
      m_transit = NULL;
    };
    

    virtual ~StateMachine()
    {
      delete [] m_entry;
      delete [] m_predo;
      delete [] m_do;
      delete [] m_postdo;
      delete [] m_exit;
    };


    /*!
     * @if jp
     * @brief NOP�ؿ�����Ͽ����
     *
     * NOP�ؿ�(���⤷�ʤ��ؿ�)����Ͽ���롣
     *
     * @param call_back ������Хå��ؿ�
     *
     * @else
     * @brief Set NOP function
     *
     * Set NOP function that does not do anything
     *
     * @param call_back Callback function
     *
     * @endif
     */
    void setNOP(Callback call_back)
    {
      setNullFunc(m_entry,  call_back);
      setNullFunc(m_do,     call_back);
      setNullFunc(m_exit,   call_back);
      setNullFunc(m_predo,  call_back);
      setNullFunc(m_postdo, call_back);
      m_transit = call_back;
    }
    
    /*!
     * @if jp
     * @brief Listener ���֥������Ȥ���Ͽ����
     *
     * �Ƽ異�������¹Ի��˸ƤӽФ���� Listener ���֥������Ȥ���Ͽ���롣
     *
     * @param listener Listener ���֥�������
     *
     * @else
     * @brief Set Listener Object
     *
     * Set Listener Object invoked when various actions are executed.
     *
     * @param listener Listener object
     *
     * @endif
     */
    void setListener(Listener* listener)
    {
      m_listener = listener;
    }
    
    /*!
     * @if jp
     * @brief Entry action �ؿ�����Ͽ����
     *
     * �ƾ��֤����ä��ݤ˼¹Ԥ���� Entry action �ѥ�����Хå��ؿ�����Ͽ���롣
     *
     * @param state ��Ͽ�оݾ���
     * @param call_back Entry action �ѥ�����Хå��ؿ�
     *
     * @return ���������¹Է��
     *
     * @else
     * @brief Set Entry action function
     *
     * Set callback function for Entry action that is executed when entering in
     * each state.
     *
     * @param state Target state for the set
     * @param call_back Callback function for Entry action
     *
     * @return Action execution result
     *
     * @endif
     */
    bool setEntryAction(State state, Callback call_back)
    {
      m_entry[state] = call_back;
      return true;
    }
    
    /*!
     * @if jp
     * @brief PreDo action �ؿ�����Ͽ����
     *
     * �ƾ�����Ǽ¹Ԥ���� PreDo action �ѥ�����Хå��ؿ�����Ͽ���롣
     *
     * @param state ��Ͽ�оݾ���
     * @param call_back PreDo action �ѥ�����Хå��ؿ�
     *
     * @return ���������¹Է��
     *
     * @else
     * @brief Set PreDo action function
     *
     * Set callback function for PreDo action that is executed in each state.
     *
     * @param state Target state for the set
     * @param call_back Callback function for PreDo action
     *
     * @return Action execution result
     *
     * @endif
     */
    bool setPreDoAction(State state, Callback call_back)
    {
      m_predo[state] = call_back;
      return true;
    }
    
    /*!
     * @if jp
     * @brief Do action �ؿ�����Ͽ����
     *
     * �ƾ�����Ǽ¹Ԥ���� Do action �ѥ�����Хå��ؿ�����Ͽ���롣
     *
     * @param state ��Ͽ�оݾ���
     * @param call_back Do action �ѥ�����Хå��ؿ�
     *
     * @return ���������¹Է��
     *
     * @else
     * @brief Set Do action function
     *
     * Set callback function for Do action that is executed in each state.
     *
     * @param state Target state for the set
     * @param call_back Callback function for Do action
     *
     * @return Action execution result
     *
     * @endif
     */
    bool setDoAction(State state, Callback call_back)
    {
      m_do[state] = call_back;
      return true;
    }
    
    /*!
     * @if jp
     * @brief PostDo action �ؿ�����Ͽ����
     *
     * �ƾ�����Ǽ¹Ԥ���� PostDo action �ѥ�����Хå��ؿ�����Ͽ���롣
     *
     * @param state ��Ͽ�оݾ���
     * @param call_back PostDo action �ѥ�����Хå��ؿ�
     *
     * @return ���������¹Է��
     *
     * @else
     * @brief Set PostDo action function
     *
     * Set callback function for PostDo action that is executed in each state.
     *
     * @param state Target state for the set
     * @param call_back Callback function for PostDo action
     *
     * @return Action execution result
     *
     * @endif
     */
    bool setPostDoAction(State state, Callback call_back)
    {
      m_postdo[state] = call_back;
      return true;
    }
    
    /*!
     * @if jp
     * @brief Exit action �ؿ�����Ͽ����
     *
     * �ƾ�����Ǽ¹Ԥ���� Exit action �ѥ�����Хå��ؿ�����Ͽ���롣
     *
     * @param state ��Ͽ�оݾ���
     * @param call_back Exit action �ѥ�����Хå��ؿ�
     *
     * @return ���������¹Է��
     *
     * @else
     * @brief Set Exit action function
     *
     * Set callback function for Exit action that is executed in each state.
     *
     * @param state Target state for the set
     * @param call_back Callback function for Exit action
     *
     * @return Action execution result
     *
     * @endif
     */
    bool setExitAction(State state, Callback call_back)
    {
      m_exit[state] = call_back;
      return true;
    }
    
    /*!
     * @if jp
     * @brief State transition action �ؿ�����Ͽ����
     *
     * �������ܻ��˼¹Ԥ���� State transition action �ѥ�����Хå��ؿ���
     * ��Ͽ���롣
     *
     * @param call_back State transition �ѥ�����Хå��ؿ�
     *
     * @return ���������¹Է��
     *
     * @else
     * @brief Set state transition action function
     *
     * Set callback function for State transition action that is executed 
     * when transiting to the state.
     *
     * @param call_back Callback function for State transition
     *
     * @return Action execution result
     *
     * @endif
     */
    bool setTransitionAction(Callback call_back)
    {
      m_transit = call_back;
      return true;
    }
    
    /*!
     * @if jp
     * @brief ������֤򥻥åȤ���
     *
     * ���ơ��ȥޥ���ν�����֤����ꤹ�롣
     *
     * @param states �������
     *
     * @else
     * @brief Set the initial state
     *
     * Set the initial state of the state machine.
     *
     * @param states Initial state
     *
     * @endif
     */
    void setStartState(States states)
    {
      m_states.curr = states.curr;
      m_states.prev = states.prev;
      m_states.next = states.next;
    }
    
    /*!
     * @if jp
     * @brief ���֤��������
     *
     * ���־����������롣
     * ���ߤξ��֡��������ξ��֡�����ͽ��ξ��֤�������뤳�Ȥ��Ǥ��롣
     *
     * @return ���־���
     *
     * @else
     * @brief Get states
     *
     * Get state information.
     * Get the current state, the previous state and the next state to
     * be expected to transfer.
     *
     * @return State information
     *
     * @endif
     */
    States getStates()
    {
      Guard guard(m_mutex);
      return m_states;
    }
    
    /*!
     * @if jp
     * @brief ���ߤξ��֤��������
     *
     * ���ߤξ��֤�������롣
     *
     * @return ���ߤξ���
     *
     * @else
     * @brief Get current state
     *
     * Get current state.
     *
     * @return Current state
     *
     * @endif
     */
    State getState()
    {
      Guard guard(m_mutex);
      return m_states.curr;
    }
    
    /*!
     * @if jp
     * @brief ���߾��֤��ǧ
     *
     * ���ߤξ��֤��������ǻ��ꤷ�����֤Ȱ��פ��뤫��ǧ���롣
     *
     * @param state ��ǧ�оݾ���
     *
     * @return ���ֳ�ǧ���
     *
     * @else
     * @brief Check current state
     *
     * Check whether current state matches the state specified by argument.
     *
     * @param state Target state for the check
     *
     * @return Check state result
     *
     * @endif
     */
    bool isIn(State state)
    {
      Guard guard(m_mutex);
      return m_states.curr == state ? true : false;
    }
    
    /*!
     * @if jp
     * @brief ���֤�����
     *
     * ���ꤷ�����֤˾��֤����ܤ��롣
     * �ܴؿ��ϼ����֤���Ū�˥��åȤ���ؿ��Ǥ��롣
     * ���Τ��ᡢ���ܤβ��ݤϡ��桼�������߾��֤������Ƚ�Ǥ�����å���
     * �������ʤ���Фʤ�ʤ���
     * �����褬���ߤξ��֤�Ʊ�����ˤϡ��������ܥե饰�򥻥åȤ��롣
     *
     * @param state ���������
     *
     * @else
     * @brief Transit State
     *
     * Transit to the specified state.
     * This function sets the next state forcibly.
     * Therefore, to determine the next state, users must get current state
     * and implement that logic.
     * If transit destination is the same as the current state, flag of
     * self-transition will be set.
     *
     * @param state State of the transition destination
     *
     * @endif
     */
    void goTo(State state)
    {
      Guard guard(m_mutex);
      m_states.next = state;
      if (m_states.curr == state)
	{
	  m_selftrans  = true;
	}
    }

    
    /*!
     * @if jp
     * @brief ��ư�ؿ�
     *
     * ���ơ��ȥޥ���ζ�ư�ؿ���
     * �ºݤξ������ܤ���Ӿ�������ȯ�����γƥ��������θƤӤ�����¹Ԥ��롣
     *
     * @else
     * @brief Worker function
     *
     * This is a worker function of the state machine.
     * Execute the invocation of each action at actual state transition and the
     * state transition occurrence.
     *
     * @endif
     */
    void worker()
    {
      States state;
      
      sync(state);
      
      if (state.curr == state.next)
	{
	  // pre-do
	  if (m_predo[state.curr] != NULL)
	    (m_listener->*m_predo [state.curr])(state);
	  
	  if (need_trans()) return;
	  
	  // do
	  if (m_do[state.curr] != NULL)
	    (m_listener->*m_do    [state.curr])(state);
	  
	  if (need_trans()) return;
	  
	  // post-do
	  if (m_postdo[state.curr] != NULL)
	    (m_listener->*m_postdo[state.curr])(state);
	}
      else
	{
	  if (m_exit[state.curr] != NULL)
	    (m_listener->*m_exit[state.curr])(state);
	  
	  sync(state);
	  
	  if (state.curr != state.next)
	    {
	      state.curr = state.next;
	      if(m_entry[state.curr] != NULL)
		(m_listener->*m_entry[state.curr])(state);
	      update_curr(state.curr);
	    }
	}
    }
    
  protected:
    /*!
     * @if jp
     * @brief NOP�ؿ�������
     *
     * NOP�ؿ�(���⤷�ʤ��ؿ�)����Ͽ���롣
     *
     * @param s ������Хå��ؿ�������
     * @param nullfunc ������Хå��ؿ�(NOP�ؿ�)
     *
     * @else
     * @brief Set NOP function
     *
     * Set NOP function (function to do nothing).
     *
     * @param s Callback function for setting
     * @param nullfunc Callback function (NOP function)
     *
     * @endif
     */
    void setNullFunc(Callback* s, Callback nullfunc)
    {
      for (int i = 0; i < m_num; ++i) s[i] = nullfunc;
    }
    
    /*!
     * @if jp
     * @brief ���ֿ�
     * @else
     * @brief Number of state
     * @endif
     */
    int m_num;
    
    /*!
     * @if jp
     * @brief ������Хå��ؿ��ѥꥹ�ʡ�
     * @else
     * @brief Callback function for listener
     * @endif
     */
    Listener* m_listener;
    
    /*!
     * @if jp
     * @brief Entry action �ѥ�����Хå��ؿ�
     * @else
     * @brief Callback function for Entry action
     * @endif
     */
    Callback* m_entry;
    
    /*!
     * @if jp
     * @brief PreDo action �ѥ�����Хå��ؿ�
     * @else
     * @brief Callback function for PreDo action
     * @endif
     */
    Callback* m_predo;
    
    /*!
     * @if jp
     * @brief Do action �ѥ�����Хå��ؿ�
     * @else
     * @brief Callback function for Do action
     * @endif
     */
    Callback* m_do;
    
    /*!
     * @if jp
     * @brief PostDo action �ѥ�����Хå��ؿ�
     * @else
     * @brief Callback function for PostDo action
     * @endif
     */
    Callback* m_postdo;
    
    /*!
     * @if jp
     * @brief Exit action �ѥ�����Хå��ؿ�
     * @else
     * @brief Callback function for Exit action
     * @endif
     */
    Callback* m_exit;
    
    /*!
     * @if jp
     * @brief State transition action �ѥ�����Хå��ؿ�
     * @else
     * @brief Callback function for State transition action
     * @endif
     */
    Callback  m_transit;
    
    /*!
     * @if jp
     * @brief ���ߤξ��־���
     * @else
     * @brief Current state information
     * @endif
     */
    States m_states;
    bool m_selftrans;
    Mutex m_mutex;
    
  private:
    inline void sync(States& st)
    {
      Guard guard(m_mutex);
      st = m_states;
    }
    
    inline bool need_trans()
    {
      Guard guard(m_mutex);
      return (m_states.curr != m_states.next);
    }
    
    inline void update_curr(const State curr)
    {
      Guard guard(m_mutex);
      m_states.curr = curr;
    }
  };
}; // namespace RTC_Utils

#endif // RTC_STATEMACHINE_H
