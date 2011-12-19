// -*- C++ -*-
/*!
 * @file  Routing.h
 * @brief Network routing information handling functions
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2010
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_ROUTING_H
#define COIL_ROUTING_H

#include <string>
 
namespace coil
{
  /*!
   * @if jp
   * @brief ����A�h���X���痘�p�����G���h�|�C���g�A�h���X�𓾂�
   * 
   * ����A�h���X��^����ƁA���̍ۂɗ��p�����G���h�|�C���g�̃A�h���X
   * ���Ԃ����B����A�h���X dest_addr �ɂ́AIP�A�h���X�܂���FQDN�z�X
   * �g����^���邱�Ƃ��ł���B����A�h���X����
   * �B�\�ł���A���p����G���h�|�C���g������ꂽ�ꍇ true�A����A�h
   * ���X�ɓ��B�ł��Ȃ��ꍇ�� false ���Ԃ����B
   *
   * @param dest_addr ����A�h���X�܂��̓z�X�g��
   * @param dest_if ����ƒʐM���s���ۂɎg�p�����C���^�[�t�F�[�X��
   * @return ���� true, ���s false
   * 
   * @else
   * @brief Getting network interface name from destination address
   *
   * This operation returns IP address of a endpoint to be used to
   * communicate with the given destination address. IP address and
   * FQDN hostname are available for the destination address
   * dest_addr. If a destination address are reachable and an endpoint
   * IP address is available, this operation returns true, and
   * otherwise false.
   *
   * @param dest_addr a destination address or host name
   * @param endpoint a IP address of the endpoint to be used to communicate
   *                 with the destination address
   * @return successful: true, failed: false
   *
   * @endif
   */
  bool dest_to_endpoint(std::string dest_addr, std::string& endpoint);

}; //namespace coil
#endif // COIL_ROUTING_H
