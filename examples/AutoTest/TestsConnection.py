#!/usr/bin/env python
# -*- coding: euc-jp -*-
#
## ConnectTest.py
##
## ����ݡ��ͥ����³�ƥ���
##

from rtc_handle import *
from BasicDataType_idl import *
import time
import commands
import SDOPackage
import os
import sys

##--------------------------------------------------------------------
g_test_name = "<< component connection test >>"

##--------------------------------------------------------------------
## ���ͥ������ץ�ե�����ǥե�������
g_interface_type1 = "corba_cdr"
g_dataflow_type = "push"
g_subscription_type = "flush"
g_push_policy = "NEW"
g_push_rate = "2000"
g_skip_count = "4"
#g_skip_count = "0"

## �ݡ����ֹ���� ( get_ports()��� )
g_port1 = 0
g_port2 = 1
g_port3 = 2

## �ǡ����ݡ��� TimedFloat
g_name1 = "out"
g_connector_id1 = "001"
g_data_type1 = "TimedFloat"

## �ǡ����ݡ��� TimedFloatSeq
g_name2 = "seqout"
g_connector_id2 = "002"
g_data_type2 = "TimedFloatSeq"

## �����ӥ��ݡ��� 
g_name3 = "MyService"
g_connector_id3 = "003"
g_interface_type3 = "MyService"

##--------------------------------------------------------------------
## ���������Ƚ���Ϣ
g_diff_send_file = "./original-data"
g_diff_recv_file = "./received-data"
g_check_message = g_diff_recv_file + " file not found."
g_test_result_file = "./ResultTest.log"
g_test_case = ""
g_test_cnt = "count"
g_test_ok = "."
g_test_ng = "F"
g_test_ng_message = "  < received-data >"
g_mess_header = "< "
g_mess_footer = " > "
# �ƥ��ȷ������
# ��)������1��1���� -> "<<< case1 count1 >>> OK."
# ��)������1��2���� -> "<<< case1 count2 >>> NG detected."

##--------------------------------------------------------------------
## �ƥ��ȥ������ֹ�ν��������
##  �夫��Ϣ�֤򿶤äƤ���
case_no = 0

## ��������Υƥ��Ȳ��
loop_count = 1

## ����¦activate_component��������¦activate_component�ޤǤΥ��꡼�׻���(�ÿ�)
sleep_recv_act_time = 1

## activate_component����deactivate_component�ޤǤΥ��꡼�׻���(�ÿ�)
sleep_act_time = 2

## for�롼�פΥ��꡼�׻���(�ÿ�)
sleep_for_time = 1

## connect����disconnect�ޤǤΥ��꡼�׻���(�ÿ�)
sleep_connect_time =1


## �͡��ॵ���С����
#env = RtmEnv(sys.argv, ["localhost:2809"])
#list0 = env.name_space["localhost:2809"].list_obj()
#env.name_space['localhost:2809'].rtc_handles.keys()
#ns = env.name_space['localhost:2809']

##
# @if jp
# @brief �ݡ��Ȥ���³���롣
# @else
# @brief Connects ports. 
# @endif
def connect_ports():

    errorFlag = True

    # �ǡ����ݡ���1 TimedFloat
    ret,porf = g_out_ports[g_port1].connect(g_conprof1)
    if ret!=RTC.RTC_OK:
        errorFlag = False

    # �ǡ����ݡ���2 TimedFloatSeq
    ret,porf = g_out_ports[g_port2].connect(g_conprof2)
    if ret!=RTC.RTC_OK:
        errorFlag = False

    # �����ӥ��ݡ��� MyService
    ret,porf = g_out_ports[g_port3].connect(g_conprof3)
    if ret!=RTC.RTC_OK:
        errorFlag = False
    

    return errorFlag
##
# @if jp
# @brief �ݡ��Ȥ����Ǥ��롣
# @else
# @brief Disconnects ports. 
# @endif
def disconnect_ports():

    errorFlag = True

    ret = g_in_ports[g_port3].disconnect(g_conprof3.connector_id)
    if ret!=RTC.RTC_OK:
        errorFlag = False
    ret = g_in_ports[g_port2].disconnect(g_conprof2.connector_id)
    if ret!=RTC.RTC_OK:
        errorFlag = False
    ret = g_in_ports[g_port1].disconnect(g_conprof1.connector_id)
    if ret!=RTC.RTC_OK:
        errorFlag = False

    return errorFlag

##
# @if jp
# @brief �ݡ��Ȥ���������롣
# @else
# @brief Activate components. 
# @endif
def activate_components(sleep_recv_act_time):
    errorFlag = True

    ret = ec_recv[0].activate_component(g_compo_recv.rtc_ref)
    if ret!=RTC.RTC_OK:
        errorFlag = False

    time.sleep(sleep_recv_act_time)

    ret = ec_send[0].activate_component(g_compo_send.rtc_ref)

    if ret!=RTC.RTC_OK:
        errorFlag = False

    return errorFlag
##
# @if jp
# @brief �ݡ��Ȥ�����������롣
# @else
# @brief Deactivate components. 
# @endif
def deactivate_components():
    errorFlag = True

    ret = ec_send[0].deactivate_component(g_compo_send.rtc_ref)
    if ret!=RTC.RTC_OK:
        errorFlag = False
    ret = ec_recv[0].deactivate_component(g_compo_recv.rtc_ref)
    if ret!=RTC.RTC_OK:
        errorFlag = False

    return errorFlag
##
# @if jp
# @brief AutoTestOut �� AutoTestIn ��ư�����롣
# @else
# @brief AutoTestOut and AutoTestIn are started. 
# @endif
def components_entry():
    global g_compo_send,g_compo_recv
    global ec_send,ec_recv
    global g_out_ports,g_in_ports
    global g_conprof1,g_conprof2,g_conprof3
    global env

    os.system('./AutoTestOutComp >/dev/null 2>&1 &') 
    os.system('./AutoTestInComp >/dev/null 2>&1 &') 

    time.sleep(2)

    #env = RtmEnv(sys.argv, ["localhost:2809"])
    list0 = env.name_space["localhost:2809"].list_obj()
    env.name_space['localhost:2809'].rtc_handles.keys()
    ns = env.name_space['localhost:2809']

    g_compo_send = ns.rtc_handles["AutoTestOut0.rtc"]
    g_compo_recv = ns.rtc_handles["AutoTestIn0.rtc"]

    ec_send = g_compo_send.rtc_ref.get_owned_contexts()
    ec_recv = g_compo_recv.rtc_ref.get_owned_contexts()

    g_out_ports = g_compo_send.rtc_ref.get_ports()
    g_in_ports = g_compo_recv.rtc_ref.get_ports()

    g_conprof3 = RTC.ConnectorProfile(g_name3, g_connector_id3, [g_out_ports[g_port3], g_in_ports[g_port3]], [SDOPackage.NameValue("dataport.interface_type",any.to_any(g_interface_type3))])

    return

##
# @if jp
# @brief AutoTestOut �� AutoTestIn ��λ�����롣
# @else
# @brief  AutoTestOut and AutoTestIn are ended. 
# @endif
def components_exit():
    g_compo_send.rtc_ref.exit();
    g_compo_recv.rtc_ref.exit();

    time.sleep(1)
    return
    
##
# @if jp
# @brief �����Х��ѿ��ν����
# @else
# @brief Initialization of global variable
# @endif
def initGlobal():
    global env

    env = RtmEnv(sys.argv, ["localhost:2809"])

    return

##--------------------------------------------------------------------
## �����ؿ������ͥ������ץ�ե���������(�ǡ����ݡ���)
##
## (����)
## subscription_type : "flush", "new", "periodic"
## push_policy       : "ALL", "FIFO", "SKIP", "NEW", ""
## connect_direction : 0:outport -> inport, 1:inport -> outport
##--------------------------------------------------------------------
def make_connecter_profile(subscription_type, push_policy, connect_direction):
    global g_conprof1, g_conprof2, g_conprof3

    if connect_direction == 0:
        ## outport -> inport Set
        g_conprof1 = RTC.ConnectorProfile(g_name1, g_connector_id1, [g_out_ports[g_port1], g_in_ports[g_port1]], [SDOPackage.NameValue("dataport.data_type",any.to_any(g_data_type1)),SDOPackage.NameValue("dataport.interface_type",any.to_any(g_interface_type1)),SDOPackage.NameValue("dataport.dataflow_type",any.to_any(g_dataflow_type)),SDOPackage.NameValue("dataport.subscription_type",any.to_any(subscription_type)),SDOPackage.NameValue("dataport.publisher.push_policy",any.to_any(push_policy)),SDOPackage.NameValue("dataport.publisher.push_rate",any.to_any(g_push_rate)),SDOPackage.NameValue("dataport.publisher.skip_count",any.to_any(g_skip_count))])

        g_conprof2 = RTC.ConnectorProfile(g_name2, g_connector_id2, [g_out_ports[g_port2], g_in_ports[g_port2]], [SDOPackage.NameValue("dataport.data_type",any.to_any(g_data_type2)),SDOPackage.NameValue("dataport.interface_type",any.to_any(g_interface_type1)),SDOPackage.NameValue("dataport.dataflow_type",any.to_any(g_dataflow_type)),SDOPackage.NameValue("dataport.subscription_type",any.to_any(subscription_type)),SDOPackage.NameValue("dataport.publisher.push_policy",any.to_any(push_policy)),SDOPackage.NameValue("dataport.publisher.push_rate",any.to_any(g_push_rate)),SDOPackage.NameValue("dataport.publisher.skip_count",any.to_any(g_skip_count))])

        #print "outport -> inport set >>>"
        #print "g_conprof1=",g_conprof1
        #print "g_conprof2=",g_conprof2
    else:
        ## inport -> outport Set
        g_conprof1 = RTC.ConnectorProfile(g_name1, g_connector_id1, [g_in_ports[g_port1], g_out_ports[g_port1]], [SDOPackage.NameValue("dataport.data_type",any.to_any(g_data_type1)),SDOPackage.NameValue("dataport.interface_type",any.to_any(g_interface_type1)),SDOPackage.NameValue("dataport.dataflow_type",any.to_any(g_dataflow_type)),SDOPackage.NameValue("dataport.subscription_type",any.to_any(subscription_type)),SDOPackage.NameValue("dataport.publisher.push_policy",any.to_any(push_policy)),SDOPackage.NameValue("dataport.publisher.push_rate",any.to_any(g_push_rate)),SDOPackage.NameValue("dataport.publisher.skip_count",any.to_any(g_skip_count))])

        g_conprof2 = RTC.ConnectorProfile(g_name2, g_connector_id2, [g_in_ports[g_port2], g_out_ports[g_port2]], [SDOPackage.NameValue("dataport.data_type",any.to_any(g_data_type2)),SDOPackage.NameValue("dataport.interface_type",any.to_any(g_interface_type1)),SDOPackage.NameValue("dataport.dataflow_type",any.to_any(g_dataflow_type)),SDOPackage.NameValue("dataport.subscription_type",any.to_any(subscription_type)),SDOPackage.NameValue("dataport.publisher.push_policy",any.to_any(push_policy)),SDOPackage.NameValue("dataport.publisher.push_rate",any.to_any(g_push_rate)),SDOPackage.NameValue("dataport.publisher.skip_count",any.to_any(g_skip_count))])

        #print "inport -> outport set >>>"
        #print "g_conprof1=",g_conprof1
        #print "g_conprof2=",g_conprof2
    return


##--------------------------------------------------------------------
## �����ؿ��������ե�������
##
## (����)
## �ʤ�
##--------------------------------------------------------------------
def delete_recv_file():
    ## �ե����뤬¸�ߤ�����
    if os.path.isfile(g_diff_recv_file) == True:
        os.remove(g_diff_recv_file)
    return


##--------------------------------------------------------------------
## �����ؿ����������ե�����Υǡ������
##
## (����)
## �ʤ�
## (�����)  True : ���ס�  False : �԰���
##--------------------------------------------------------------------
def diff_file():
    bret = True

    ## if connect_direction == 0:
    ## else:
    ## �����ե�����̵ͭȽ��
    if os.path.isfile(g_diff_send_file) == False:
        print "send_file (%s) not found." % send_file
        return False

    ## �����ե�����̵ͭȽ��
    if os.path.isfile(g_diff_recv_file) == False:
        print "recv_file (%s) not found." % recv_file
        return False

    ## �������ǡ�����ʬȽ��
    f_send = open(g_diff_send_file, 'r')
    f_recv = open(g_diff_recv_file, 'r')

    while(1):
        str_send = f_send.readline()
        str_recv = f_recv.readline()
        if len(str_send) == 0:
            break

        #print "original send date=(%s)" % str_send
        #print ''.join(['%x ' % ord(s) for s in str_send])
        #print "original recv date=(%s)" % str_recv
        #print ''.join(['%x ' % ord(s) for s in str_recv])

        ## �����β��ԡ����������ɺ��
        str_send2 = str_send.rstrip('\n')
        str_send2 = str_send2.rstrip('\r')
        str_recv2 = str_recv.rstrip('\n')
        str_recv2 = str_recv2.rstrip('\r')

        #print "rstrip after send date=(%s)" % str_send2
        #print "rstrip after recv date=(%s)" % str_recv2

        ## �ǡ������
        list_send = str_send2.split(" ")
        list_recv = str_recv2.split(" ")
        for ic in range(len(list_send)):
            try:
                float_send = float(list_send[ic]);
                float_recv = float(list_recv[ic]);
                if float_send != float_recv:
                    bret = False
                    break;
            except:
                if str_send2 != str_recv2:
                    bret = False
                    break;
         

    f_recv.close()
    f_send.close()
    return bret


##
# @if jp
# @brief ��³�����Ǥ����򷫤��֤���
#
#
#
# @else
# @brief Only the connection and cutting are repeated. 
#
#
#
# @endif
def test_connect_disconnect(message,arg0,arg1,arg2):

    errorFlag = True
    for i in range(loop_count):

        ## 1 ���ͥ������ץ�ե���������
        make_connecter_profile(arg0,arg1,arg2)

        ## 3 �ݡ�����³
        bool_ret = connect_ports()
        if bool_ret!=True:
            errorFlag = False

        time.sleep(sleep_connect_time)

        ## 6 �ݡ�������
        bool_ret = disconnect_ports()
        if bool_ret!=True:
            errorFlag = False

        ## �ƥ��ȷ�̽���
        fout = open(g_test_result_file, 'a')
        if errorFlag:
            message = g_test_ok
        else :
            message = g_test_ng
        print message ,
        sys.stdout.flush()
        fout.write(message)
        fout.close()

        time.sleep(sleep_for_time)

    return errorFlag

    
##
# @if jp
# @brief Activate��Deactivate�����򷫤��֤���
#
# ��³�������֤� Activate �� Deactivate �򷫤��֤���
# �ǡ����Υ����å��ϹԤ��ʤ���
#
# @else
# @brief Only activation and deactivation are repeated. 
#
# Activate and Deactivate are repeated while connected. 
# Data is not checked. 
#
# @endif
def test_activate_deactivate_2(message,arg0,arg1,arg2):
    
    errorFlag = True
    ## 1 ���ͥ������ץ�ե���������
    make_connecter_profile(arg0,arg1,arg2)
    
    ## 3 �ݡ�����³
    bool_ret = connect_ports()
    if bool_ret!=True:
        errorFlag = False
    
    for i in range(loop_count):
    
        ## 2 �����ǡ����ե�������
        delete_recv_file()
    
        ## 4 �����ƥ��١���
        bool_ret = activate_components(sleep_recv_act_time)
        if bool_ret!=True:
            errorFlag = False
    
        time.sleep(sleep_act_time)
    
        ## 5 �ǥ������ƥ��١���
        bool_ret = deactivate_components()
        if bool_ret!=True:
            errorFlag = False
    
        ## �����ե�����̵ͭȽ��
        if os.path.isfile(g_diff_recv_file) == False:
            errorFlag = False
            fout = open(g_test_result_file, 'a')
            #message = message + g_check_message
            message = g_test_ng
            fout.write(message)
            fout.close()
            print message ,
            sys.stdout.flush()
            time.sleep(sleep_for_time)
            continue
    
        ## �ե����륵����������å�����
        time.sleep(sleep_act_time)
        fout = open(g_test_result_file, 'a')
        fsize=os.path.getsize(g_diff_recv_file)
        if fsize > 0:
            message = g_test_ok
            print message ,
            sys.stdout.flush()
            fout.write(message)
        else:
            errorFlag = False
            # �ƥ��ȷ�� NG
            message = g_test_ng
            print message ,
            sys.stdout.flush()
            fout.write(message)

        fout.close()
    
        time.sleep(sleep_for_time)
    
    ## 6 �ݡ�������
    bool_ret = disconnect_ports()

    return errorFlag
##
# @if jp
# @brief Activate��Deactivate�����򷫤��֤���
#
# ��³�������֤� Activate �� Deactivate �򷫤��֤���
#
# @else
# @brief Only activation and deactivation are repeated. 
#
# Activate and Deactivate are repeated while connected. 
#
# @endif
def test_activate_deactivate(message,arg0,arg1,arg2):
    
    errorFlag = True
    ## 1 ���ͥ������ץ�ե���������
    make_connecter_profile(arg0,arg1,arg2)
    
    ## 3 �ݡ�����³
    bool_ret = connect_ports()
    if bool_ret!=True:
        errorFlag = False
    
    for i in range(loop_count):
    
        ## 2 �����ǡ����ե�������
        delete_recv_file()
    
        ## 4 �����ƥ��١���
        bool_ret = activate_components(sleep_recv_act_time)
        if bool_ret!=True:
            errorFlag = False
    
        time.sleep(sleep_act_time)
    
        ## 5 �ǥ������ƥ��١���
        bool_ret = deactivate_components()
        if bool_ret!=True:
            errorFlag = False
    
        ## �����ե�����̵ͭȽ��
        if os.path.isfile(g_diff_recv_file) == False:
            errorFlag = False
            fout = open(g_test_result_file, 'a')
            #message = message + g_check_message
            message = g_test_ng
            fout.write(message)
            fout.close()
            print message ,
            sys.stdout.flush()
            time.sleep(sleep_for_time)
            continue
    
        ## 7 �������ǡ������
        time.sleep(sleep_act_time)
        bret = diff_file()
    
        ## ��ʬ�ե����뤫��ƥ��ȷ�̽���
        fout = open(g_test_result_file, 'a')
        # bret==True �ʤ��������ǡ�������
        if bret == True:
            # �ƥ��ȷ�� OK
            message = g_test_ok
            print message ,
            sys.stdout.flush()
            fout.write(message + '\n')
        else:
            errorFlag = False
            # �ƥ��ȷ�� NG
            message = g_test_ng
            print message ,
            sys.stdout.flush()
            fout.write(message + '\n')
            # �����ǡ�����ƥ��ȷ�̥ե�����إ��ԡ�
            fin2 = open(g_diff_recv_file, 'r')
            while(1):
                s2 = fin2.readline()
                if len(s2) == 0:
                    break
                fout.write(s2)
            fin2.close()
        fout.close()
    
        time.sleep(sleep_for_time)
    
    ## 6 �ݡ�������
    bool_ret = disconnect_ports()

    return errorFlag
    
##
# @if jp
# @brief Activate��Deactivate�����򷫤��֤���
#
# ��³������ Activate �� Deactivate �򷫤��֤���
#
# @else
# @brief Only activation and deactivation are repeated. 
#
# Activate and Deactivate are repeated without connecting it. 
#
# @endif
def test_activate_deactivate_2(message,arg0,arg1,arg2):
    
    errorFlag = True
    
    for i in range(loop_count):
    
        ## 1 ���ͥ������ץ�ե���������
        make_connecter_profile(arg0,arg1,arg2)
    
        ## 4 �����ƥ��١���
        bool_ret = activate_components(sleep_recv_act_time)
        if bool_ret!=True:
            errorFlag = False
    
        time.sleep(sleep_act_time)
    
        ## 5 �ǥ������ƥ��١���
        bool_ret = deactivate_components()
        if bool_ret!=True:
            errorFlag = False
    
        ## �ƥ��ȷ�̽���
        fout = open(g_test_result_file, 'a')
        if errorFlag:
            message = g_test_ok
        else :
            message = g_test_ng
        print message ,
        sys.stdout.flush()
        fout.write(message)
        fout.close()
    
        time.sleep(sleep_for_time)

    return errorFlag
    
##
# @if jp
# @brief ��³��activate��deactivate�����Ǥ򷫤��֤��� 
#
# �ǡ����Υ����å��ϹԤ��ʤ���
# periodic,new����³�ƥ��ȤǤϡ��ݥꥷ����SKIP,NEW�ξ�硢
# �ǡ����γ�ǧ�ϹԤ�ʤ���
#
#
# @else
# @brief The connection, activate, deactivate, and cutting are repeated. 
#
# Data is not checked. 
#
# @endif
def test_connection_5(message,arg0,arg1,arg2):
    
    errorFlag = True
    for i in range(loop_count):
    
        ## 2 �����ǡ����ե�������
        delete_recv_file()
    
        ## 1 ���ͥ������ץ�ե���������
        make_connecter_profile(arg0,arg1,arg2)
    
        ## 3 �ݡ�����³
        bool_ret = connect_ports()
        if bool_ret!=True:
            errorFlag = False

        ## 4 �����ƥ��١���
        bool_ret = activate_components(sleep_recv_act_time)
        if bool_ret!=True:
            errorFlag = False
    
        time.sleep(sleep_act_time)
    
        ## 5 �ǥ������ƥ��١���
        bool_ret = deactivate_components()
        if bool_ret!=True:
            errorFlag = False
    
        ## 6 �ݡ�������
        bool_ret = disconnect_ports()
        if bool_ret!=True:
            errorFlag = False
    
        ## �����ե�����̵ͭȽ��
        if os.path.isfile(g_diff_recv_file) == False:
            errorFlag = False
            fout = open(g_test_result_file, 'a')
            message = g_test_ng
            fout.write(message + '\n')
            fout.close()
            print message,
            sys.stdout.flush()
            time.sleep(sleep_for_time)
            continue
    
        ## �ե����륵����������å�����
        time.sleep(sleep_act_time)
        fout = open(g_test_result_file, 'a')
        fsize=os.path.getsize(g_diff_recv_file)
        if fsize > 0:
            message = g_test_ok
            print message ,
            sys.stdout.flush()
            fout.write(message)
        else:
            errorFlag = False
            # �ƥ��ȷ�� NG
            message = g_test_ng
            print message ,
            sys.stdout.flush()
            fout.write(message)

        fout.close()
    
        time.sleep(sleep_for_time)

    return errorFlag
##
# @if jp
# @brief ��³��activate��deactivate�����Ǥ򷫤��֤��� 
#
#
# @else
# @brief The connection, activate, deactivate, and cutting are repeated. 
#
#
# @endif
def test_connection(message,arg0,arg1,arg2):
    
    errorFlag = True
    for i in range(loop_count):
    
        ## 2 �����ǡ����ե�������
        delete_recv_file()
    
        ## 1 ���ͥ������ץ�ե���������
        make_connecter_profile(arg0,arg1,arg2)
    
        ## 3 �ݡ�����³
        bool_ret = connect_ports()
        if bool_ret!=True:
            errorFlag = False
    
        ## 4 �����ƥ��١���
        bool_ret = activate_components(sleep_recv_act_time)
        if bool_ret!=True:
            errorFlag = False
    
        time.sleep(sleep_act_time)
    
        ## 5 �ǥ������ƥ��١���
        bool_ret = deactivate_components()
        if bool_ret!=True:
            errorFlag = False
    
        ## 6 �ݡ�������
        bool_ret = disconnect_ports()
        if bool_ret!=True:
            errorFlag = False

    
        ## �����ե�����̵ͭȽ��
        if os.path.isfile(g_diff_recv_file) == False:
            errorFlag = False
            fout = open(g_test_result_file, 'a')
            message = g_test_ng
            fout.write(message + '\n')
            fout.close()
            print message,
            sys.stdout.flush()
            time.sleep(sleep_for_time)
            continue
    
        ## 7 �������ǡ������
        time.sleep(sleep_act_time)
        bret = diff_file()
    
        ## ��ʬ�ե����뤫��ƥ��ȷ�̽���
        fout = open(g_test_result_file, 'a')
        # bret==True �ʤ��������ǡ�������
        if bret == True:
            # �ƥ��ȷ�� OK
            message = g_test_ok
            print message ,
            sys.stdout.flush()
            fout.write(message + '\n')
        else:
            errorFlag = False
            # �ƥ��ȷ�� NG
            message = g_test_ng
            print message ,
            sys.stdout.flush()
            fout.write(message + '\n')
            # �����ǡ�����ƥ��ȷ�̥ե�����إ��ԡ�
            fin2 = open(g_diff_recv_file, 'r')
            while(1):
                s2 = fin2.readline()
                if len(s2) == 0:
                    break
                fout.write(s2)
            fin2.close()
        fout.close()
    
        time.sleep(sleep_for_time)

    return errorFlag
    
    
##
# @if jp
# @brief ��³��activate�����ǡ�deactivate�򷫤��֤��� 
#
#
# @else
# @brief 
#
#
# @endif
def test_connection_2(message,arg0,arg1,arg2):
    
    errorFlag = True
    
    for i in range(loop_count):
    
        ## 2 �����ǡ����ե�������
        delete_recv_file()
    
        ## 1 ���ͥ������ץ�ե���������
        make_connecter_profile("flush", "", 0)
    
        ## 3 �ݡ�����³
        bool_ret = connect_ports()
        if bool_ret!=True:
            errorFlag = False
    
        ## 4 �����ƥ��١���
        bool_ret = activate_components(sleep_recv_act_time)
        if bool_ret!=True:
            errorFlag = False
    
        time.sleep(sleep_act_time)
    
        ## 6 �ݡ�������
        bool_ret = disconnect_ports()
        if bool_ret!=True:
            errorFlag = False
    
        ## 5 �ǥ������ƥ��١���
        bool_ret = deactivate_components()
        if bool_ret!=True:
            errorFlag = False
    
        ## �����ե�����̵ͭȽ��
        if os.path.isfile(g_diff_recv_file) == False:
            errorFlag = False
            fout = open(g_test_result_file, 'a')
            message = g_test_ng
            fout.write(message + '\n')
            fout.close()
            print message,
            sys.stdout.flush()
            time.sleep(sleep_for_time)
            continue
    
        ## 7 �������ǡ������
        time.sleep(sleep_act_time)
        bret = diff_file()
    
        ## ��ʬ�ե����뤫��ƥ��ȷ�̽���
        fout = open(g_test_result_file, 'a')
        # bret==True �ʤ��������ǡ�������
        if bret == True:
            # �ƥ��ȷ�� OK
            message = g_test_ok
            print message ,
            sys.stdout.flush()
            fout.write(message + '\n')
        else:
            errorFlag = False
            # �ƥ��ȷ�� NG
            message = g_test_ng
            print message ,
            sys.stdout.flush()
            fout.write(message + '\n')
            # �����ǡ�����ƥ��ȷ�̥ե�����إ��ԡ�
            fin2 = open(g_diff_recv_file, 'r')
            while(1):
                s2 = fin2.readline()
                if len(s2) == 0:
                    break
                fout.write(s2)
            fin2.close()
        fout.close()
        ## ��ʬ�ե����뤫��ƥ��ȷ�̽���
        time.sleep(sleep_for_time)

    return errorFlag
    
    
##
# @if jp
# @brief activate����³��deactivate�����Ǥ򷫤��֤��� 
#
#  �ǡ����Υ����å��ϹԤ��ʤ��� 
#  ��ա�Activate����˹ԤäƤ���١������ǡ��������椫������Ƥˤʤ�ޤ���
#  periodic,new����³�ƥ��ȤǤϡ��ݥꥷ����SKIP,NEW�ξ�硢
#  �ǡ����γ�ǧ�ϹԤ�ʤ���
#
# @else
# @brief 
#
#
# @endif
def test_connection_3(message,arg0,arg1,arg2):
    
    errorFlag = True

    for i in range(loop_count):
    
        ## 2 �����ǡ����ե�������
        delete_recv_file()
    
        ## 1 ���ͥ������ץ�ե���������
        make_connecter_profile(arg0,arg1,arg2)
    
        ## 4 �����ƥ��١���
        bool_ret = activate_components(sleep_recv_act_time)
        if bool_ret!=True:
            errorFlag = False
    
        ## 3 �ݡ�����³
        bool_ret = connect_ports()
        if bool_ret!=True:
            errorFlag = False
    
        time.sleep(sleep_act_time)
    
        ## 5 �ǥ������ƥ��١���
        bool_ret = deactivate_components()
        if bool_ret!=True:
            errorFlag = False
    
        ## 6 �ݡ�������
        bool_ret = disconnect_ports()
        if bool_ret!=True:
            errorFlag = False
    
        ## �����ե�����̵ͭȽ��
        if os.path.isfile(g_diff_recv_file) == False:
            errorFlag = False
            fout = open(g_test_result_file, 'a')
            message = g_test_ng
            fout.write(message + '\n')
            fout.close()
            print message,
            sys.stdout.flush()
            time.sleep(sleep_for_time)
            continue
    
        ## 7 �������ǡ������
        time.sleep(sleep_act_time)
        fout = open(g_test_result_file, 'a')
        fsize=os.path.getsize(g_diff_recv_file)
        if fsize > 0:
            message = g_test_ok
            print message ,
            sys.stdout.flush()
            fout.write(message)
        else:
            errorFlag = False
            # �ƥ��ȷ�� NG
            message = g_test_ng
            print message ,
            sys.stdout.flush()
            fout.write(message)

        fout.close()
    
        time.sleep(sleep_for_time)
    
    return errorFlag

    
##
# @if jp
# @brief activate����³�����ǡ�deactivate�򷫤��֤��� 
#
#  �ǡ����Υ����å��ϹԤ��ʤ��� 
#  ��ա�Activate����˹ԤäƤ���١������ǡ��������椫������Ƥˤʤ�ޤ���
#  periodic,new����³�ƥ��ȤǤϡ��ݥꥷ����SKIP,NEW�ξ�硢
#  �ǡ����γ�ǧ�ϹԤ�ʤ���
#
# @else
# @brief 
#
#
# @endif
def test_connection_4(message,arg0,arg1,arg2):
    
    errorFlag = True
    for i in range(loop_count):
    
        ## 2 �����ǡ����ե�������
        delete_recv_file()
    
        ## 1 ���ͥ������ץ�ե���������
        make_connecter_profile(arg0,arg1,arg2)
    
        ## 4 �����ƥ��١���
        bool_ret = activate_components(sleep_recv_act_time)
        if bool_ret!=True:
            errorFlag = False
    
        ## 3 �ݡ�����³
        bool_ret = connect_ports()
        if bool_ret!=True:
            errorFlag = False
    
        time.sleep(sleep_act_time)
    
        ## 6 �ݡ�������
        bool_ret = disconnect_ports()
        if bool_ret!=True:
            errorFlag = False
    
        ## 5 �ǥ������ƥ��١���
        bool_ret = deactivate_components()
        if bool_ret!=True:
            errorFlag = False
    
        ## �����ե�����̵ͭȽ��
        if os.path.isfile(g_diff_recv_file) == False:
            errorFlag = False
            fout = open(g_test_result_file, 'a')
            message = g_test_ng
            fout.write(message + '\n')
            fout.close()
            print message,
            sys.stdout.flush()
            time.sleep(sleep_for_time)
            continue
    
        ## 7 �������ǡ������
        time.sleep(sleep_act_time)
        fout = open(g_test_result_file, 'a')
        fsize=os.path.getsize(g_diff_recv_file)
        if fsize > 0:
            message = g_test_ok
            print message ,
            sys.stdout.flush()
            fout.write(message)
        else:
            errorFlag = False
            # �ƥ��ȷ�� NG
            message = g_test_ng
            print message ,
            sys.stdout.flush()
            fout.write(message)

        fout.close()
    
        time.sleep(sleep_for_time)

    return errorFlag
    
##
# @if jp
# @brief �ƥ��ȥơ��֥�
# @else
# @brief Test table
# @endif
test_table = [
    [ test_connect_disconnect,
      "Connect(out->in, flush) -> Disconnect",
      "flush", "", 0 ],
    [ test_connect_disconnect,
      "Connect(in->out, flush) -> Disconnect",
      "flush", "", 1 ],
    [ test_activate_deactivate,
      "Connecting(out->in, flush), Activate -> send/recv -> Deactivate",
      "flush", "", 0 ],
    [ test_activate_deactivate,
      "Connecting(in->out, flush), Activate -> send/recv -> Deactivate",
      "flush", "", 1 ],
    [ test_activate_deactivate_2,
      "Not Connect(out->in, flush), Activate -> Deactivate",
      "flush", "", 0 ],
    [ test_connection,
      "Connect(out->in, flush) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "flush", "", 0 ],
    [ test_connection,
      "Connect(in->out, flush) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "flush", "", 1 ],
    [ test_connection_2,
      "Connect(out->in, flush) -> Activate -> send/recv -> Disconnect -> Deactivate",
      "flush", "", 0 ],
    [ test_connection_2,
      "Connect(in->out, flush) -> Activate -> send/recv -> Disconnect -> Deactivate",
      "flush", "", 1 ],
    [ test_connection_3,
      "Activate -> Connect(out->in, flush) -> send/recv -> Deactivate -> Disconnect",
      "flush", "", 0 ],
    [ test_connection_3,
      "Activate -> Connect(in->out, flush) -> send/recv -> Deactivate -> Disconnect",
      "flush", "", 1 ],
    [ test_connection_4,
      "Activate -> Connect(out->in, flush) -> send/recv -> Disconnect -> Deactivate",
      "flush", "", 0 ],
    [ test_connection_4,
      "Activate -> Connect(in->out, flush) -> send/recv -> Disconnect -> Deactivate",
      "flush", "", 1 ],
    [ test_connect_disconnect,
      "Connect(out->in, new,ALL) -> Disconnect",
      "new", "ALL", 0 ],
    [ test_connect_disconnect,
      "Connect(out->in, new,FIFO) -> Disconnect",
      "new", "FIFO", 0 ],
    [ test_connect_disconnect,
      "Connect(out->in, new,NEW) -> Disconnect",
      "new", "NEW", 0 ],
    [ test_connect_disconnect,
      "Connect(out->in, new,SKIP) -> Disconnect",
      "new", "SKIP", 0 ],
    [ test_connect_disconnect,
      "Connect(in->out, new,ALL) -> Disconnect",
      "new", "ALL", 1 ],
    [ test_connect_disconnect,
      "Connect(in->out, new,FIFO) -> Disconnect",
      "new", "FIFO", 1 ],
    [ test_connect_disconnect,
      "Connect(in->out, new,NEW) -> Disconnect",
      "new", "NEW", 1 ],
    [ test_connect_disconnect,
      "Connect(in->out, new,SKIP) -> Disconnect",
      "new", "SKIP", 1 ],
    [ test_activate_deactivate,
      "Connecting(out->in, new,ALL), Activate -> send/recv -> Deactivate",
      "new", "ALL", 0 ],
    [ test_activate_deactivate,
      "Connecting(out->in, new,FIFO), Activate -> send/recv -> Deactivate",
      "new", "FIFO", 0 ],
    [ test_activate_deactivate,
      "Connecting(out->in, new,NEW), Activate -> send/recv -> Deactivate",
      "new", "NEW", 0 ],
    [ test_activate_deactivate_2,
      "Connecting(out->in, new,SKIP), Activate -> send/recv -> Deactivate",
      "new", "SKIP", 0 ],
    [ test_activate_deactivate,
      "Connecting(in->out, new,ALL), Activate -> send/recv -> Deactivate",
      "new", "ALL", 1 ],
    [ test_activate_deactivate,
      "Connecting(in->out, new,FIFO), Activate -> send/recv -> Deactivate",
      "new", "FIFO", 1 ],
    [ test_activate_deactivate_2,
      "Connecting(in->out, new,NEW), Activate -> send/recv -> Deactivate",
      "new", "NEW", 1 ],
    [ test_activate_deactivate_2,
      "Connecting(in->out, new,SKIP), Activate -> send/recv -> Deactivate",
      "new", "SKIP", 1 ],
    [ test_connection,
      "Connect(out->in, new,ALL) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "new", "ALL", 0 ],
    [ test_connection,
      "Connect(out->in, new,FIFO) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "new", "FIFO", 0 ],
    [ test_connection_5,
      "Connect(out->in, new,NEW) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "new", "NEW", 0 ],
    [ test_connection_5,
      "Connect(out->in, new,SKIP) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "new", "SKIP", 0 ],
    [ test_connection,
      "Connect(in->out, new,ALL) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "new", "ALL", 1 ],
    [ test_connection,
      "Connect(in->out, new,FIFO) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "new", "FIFO", 1 ],
    [ test_connection_5,
      "Connect(in->out, new,NEW) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "new", "NEW", 1 ],
    [ test_connection_5,
      "Connect(in->out, new,SKIP) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "new", "SKIP", 1 ],
    [ test_connect_disconnect,
      "Connect(out->in, periodic,ALL) -> Disconnect",
      "periodic", "ALL", 0 ],
    [ test_connect_disconnect,
      "Connect(out->in, periodic,FIFO) -> Disconnect",
      "periodic", "FIFO", 0 ],
    [ test_connect_disconnect,
      "Connect(out->in, periodic,NEW) -> Disconnect",
      "periodic", "NEW", 0 ],
    [ test_connect_disconnect,
      "Connect(out->in, periodic,SKIP) -> Disconnect",
      "periodic", "SKIP", 0 ],
    [ test_connect_disconnect,
      "Connect(in->out, periodic,ALL) -> Disconnect",
      "periodic", "ALL", 1 ],
    [ test_connect_disconnect,
      "Connect(in->out, periodic,FIFO) -> Disconnect",
      "periodic", "FIFO", 1 ],
    [ test_connect_disconnect,
      "Connect(in->out, periodic,NEW) -> Disconnect",
      "periodic", "NEW", 1 ],
    [ test_connect_disconnect,
      "Connect(in->out, periodic,SKIP) -> Disconnect",
      "periodic", "SKIP", 1 ],
    [ test_activate_deactivate,
      "Connecting(out->in, periodic,ALL), Activate -> send/recv -> Deactivate",
      "periodic", "ALL", 0 ],
    [ test_activate_deactivate,
      "Connecting(out->in, periodic,FIFO), Activate -> send/recv -> Deactivate",
      "periodic", "FIFO", 0 ],
    [ test_activate_deactivate_2,
      "Connecting(out->in, periodic,NEW), Activate -> send/recv -> Deactivate",
      "periodic", "NEW", 0 ],
    [ test_activate_deactivate_2,
      "Connecting(out->in, periodic,SKIP), Activate -> send/recv -> Deactivate",
      "periodic", "SKIP", 0 ],
    [ test_activate_deactivate,
      "Connecting(in->out, periodic,ALL), Activate -> send/recv -> Deactivate",
      "periodic", "ALL", 1 ],
    [ test_activate_deactivate,
      "Connecting(in->out, periodic,FIFO), Activate -> send/recv -> Deactivate",
      "periodic", "FIFO", 1 ],
    [ test_activate_deactivate_2,
      "Connecting(in->out, periodic,NEW), Activate -> send/recv -> Deactivate",
      "periodic", "NEW", 1 ],
    [ test_activate_deactivate_2,
      "Connecting(in->out, periodic,SKIP), Activate -> send/recv -> Deactivate",
      "periodic", "SKIP", 1 ],
    [ test_connection,
      "Connect(out->in, periodic,ALL) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "periodic", "ALL", 0 ],
    [ test_connection,
      "Connect(out->in, periodic,FIFO) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "periodic", "FIFO", 0 ],
    [ test_connection_5,
      "Connect(out->in, periodic,NEW) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "periodic", "NEW", 0 ],
    [ test_connection_5,
      "Connect(out->in, periodic,SKIP) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "periodic", "SKIP", 0 ],
    [ test_connection,
      "Connect(in->out, periodic,ALL) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "periodic", "ALL", 1 ],
    [ test_connection,
      "Connect(in->out, periodic,FIFO) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "periodic", "FIFO", 1 ],
    [ test_connection_5,
      "Connect(in->out, periodic,NEW) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "periodic", "NEW", 1 ],
    [ test_connection_5,
      "Connect(in->out, periodic,SKIP) -> Activate -> send/recv -> Deactivate -> Disconnect",
      "periodic", "SKIP", 1 ],

]
##
# @if jp
# @brief main
# @else
# @brief main
# @endif
def main():
    
    initGlobal()
    ok_counter = 0
    ng_counter = 0

    exit = 0
    result_message = ""
    for element in test_table:
        components_entry()
        
        message = g_mess_header + g_test_case 
        message = message + element[1]
        message = message + g_mess_footer
        fout = open(g_test_result_file, 'a')
        fout.write('\n' + message)
        fout.close()
        print "" 
        print message
        ret = element[0](message,element[2],element[3],element[4])
        components_exit()
        if ret == False:
            ng_counter = ng_counter + 1
            exit = 1
            result_message = "!!!FAILURES!!!"
            break;
        else :
            ok_counter = ok_counter + 1
        

    print ""
    print result_message 
    print "Test Results: " 
    print "Run:",ok_counter+ng_counter,"   Failures:", ng_counter
    return exit 
if __name__ == "__main__":
  main()
