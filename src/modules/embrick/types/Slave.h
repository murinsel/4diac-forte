/*******************************************************************************
 * Copyright (c) 2016 Johannes Messmer (admin@jomess.com)
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Johannes Messmer - initial API and implementation and/or initial documentation
 *******************************************************************************/

#ifndef SRC_MODULES_EMBRICK_TYPES_SLAVE_H_
#define SRC_MODULES_EMBRICK_TYPES_SLAVE_H_

#include <funcbloc.h>
#include "BusAdapter.h"
#include <forte_sync.h>

#include <handler/bus.h>
#include <slave/slave.h>
#include <slave/handle.h>

namespace EmBrick {
namespace FunctionBlocks {

class Slave: public CFunctionBlock, public EmBrick::Slave::Delegate {
public:
  Slave(CResource *pa_poSrcRes, const SFBInterfaceSpec *pa_pstInterfaceSpec,
      const CStringDictionary::TStringId pa_nInstanceNameId,
      TForteByte *pa_acFBConnData, TForteByte *pa_acFBVarsData);
  virtual ~Slave();

protected:
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  }

  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  }

  static const TEventID scm_nEventREQID = 0;
  static const TEventID scm_nEventMAPID = 1;

  BusAdapter& BusAdapterOut() {
    return (*static_cast<BusAdapter*>(m_apoAdapters[0]));
  }

  static const int scm_nBusAdapterOutAdpNum = 0;
  BusAdapter& BusAdapterIn() {
    return (*static_cast<BusAdapter*>(m_apoAdapters[1]));
  }

  static const int scm_nBusAdapterInAdpNum = 1;

  virtual void executeEvent(int pa_nEIID);

  SlaveType type;
  CSyncObject slaveMutex;
  EmBrick::Slave *slave;
  bool ready;

  virtual bool init(int index);
  virtual void initHandles() = 0;
  void dropHandles();

  void addBitHandle(IOHandle::Direction direction, CIEC_WSTRING id,
      uint8_t offset, uint8_t pos);

public:
  void onSlaveDestroy();
};

} /* namespace FunctionsBlocks */
} /* namespace EmBrick */

#endif /* SRC_MODULES_EMBRICK_TYPES_SLAVE_H_ */
