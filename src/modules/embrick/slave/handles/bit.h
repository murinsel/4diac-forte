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

#ifndef SRC_MODULES_EMBRICK_SLAVE_HANDLES_BIT_H_
#define SRC_MODULES_EMBRICK_SLAVE_HANDLES_BIT_H_

#include <slave/slave.h>
#include <slave/handle.h>

class EmbrickBitSlaveHandle: public EmbrickSlaveHandle {
public:
  EmbrickBitSlaveHandle(forte::core::IO::IODeviceController *controller, forte::core::IO::IOMapper::Direction direction,
      uint8_t offset, uint8_t position, EmbrickSlaveHandler *slave);

  virtual void set(const CIEC_ANY &);
  void get(CIEC_ANY &);

  bool equal(unsigned char* oldBuffer);

protected:
  virtual void reset() {
    CIEC_BOOL s = false;
    set(s);
  }

protected:
  const uint8_t mask;
};

#endif /* SRC_MODULES_EMBRICK_SLAVE_HANDLES_BIT_H_ */
