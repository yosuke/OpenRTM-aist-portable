// -*- C++ -*-
/*!
 * @file ConsoleInComp.cpp
 * @brief Standalone component
 * @date $Date: 2008-01-14 07:45:55 $
 *
 * $Id: ConsoleInComp.cpp 778 2008-07-29 04:59:25Z n-ando $
 */

#include <rtm/Manager.h>
#include <iostream>
#include <string>
#include "ConsoleIn.h"
#include <rtm/NVUtil.h>


void MyModuleInit(RTC::Manager* manager)
{
  ConsoleInInit(manager);
  RTC::RtcBase* comp;

  // Create a component
  std::cout << "Creating a component: \"ConsoleIn\"....";
  comp = manager->createComponent("ConsoleIn");
  std::cout << "succeed." << std::endl;

  RTC::ComponentProfile_var prof;
  prof = comp->get_component_profile();
  std::cout << "=================================================" << std::endl;
  std::cout << " Component Profile" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << "InstanceID:     " << prof->instance_name << std::endl;
  std::cout << "Implementation: " << prof->type_name << std::endl;
  std::cout << "Description:    " << prof->description << std::endl;
  std::cout << "Version:        " << prof->version << std::endl;
  std::cout << "Maker:          " << prof->vendor << std::endl;
  std::cout << "Category:       " << prof->category << std::endl;
  std::cout << "  Other properties   " << std::endl;
  NVUtil::dump(prof->properties);
  std::cout << "=================================================" << std::endl;

  PortServiceList* portlist;
  portlist = comp->get_ports();

  for (CORBA::ULong i(0), n(portlist->length()); i < n; ++i)
    {
      PortService_ptr port;
      port = (*portlist)[i];
      std::cout << "================================================="
		<< std::endl;
      std::cout << "Port" << i << " (name): ";
      std::cout << port->get_port_profile()->name << std::endl;
      std::cout << "-------------------------------------------------"
		<< std::endl;    
      RTC::PortInterfaceProfileList iflist;
      iflist = port->get_port_profile()->interfaces;

      for (CORBA::ULong i(0), n(iflist.length()); i < n; ++i)
	{
	  std::cout << "I/F name: ";
	  std::cout << iflist[i].instance_name << std::endl;
	  std::cout << "I/F type: ";
	  std::cout << iflist[i].type_name << std::endl;
	  const char* pol;
	  pol = iflist[i].polarity == 0 ? "PROVIDED" : "REQUIRED";
	  std::cout << "Polarity: " << pol << std::endl;
	}
      std::cout << "- properties -" << std::endl;
      NVUtil::dump(port->get_port_profile()->properties);
      std::cout << "-------------------------------------------------" << std::endl;
    }
  return;
}



int main (int argc, char** argv)
{
  RTC::Manager* manager;
  manager = RTC::Manager::init(argc, argv);

  // Set module initialization proceduer
  // This procedure will be invoked in activateManager() function.
  manager->setModuleInitProc(MyModuleInit);

  // Activate manager and register to naming service
  manager->activateManager();

  // run the manager in blocking mode
  // runManager(false) is the default.
  manager->runManager();

  // If you want to run the manager in non-blocking mode, do like this
  // manager->runManager(true);

  return 0;
}
