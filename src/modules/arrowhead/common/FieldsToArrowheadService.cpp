/*******************************************************************************
 * Copyright (c) 2018, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *******************************************************************************/

#include "FieldsToArrowheadService.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FieldsToArrowheadService_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_FieldsToArrowheadService, g_nStringIdFieldsToArrowheadService)

const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scm_anDataInputNames[] = {g_nStringIdserviceDefinition, g_nStringIdinterfaces, g_nStringIdserviceMetadata};

const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scm_anDataInputTypeIds[] = {g_nStringIdWSTRING, g_nStringIdARRAY, 10, g_nStringIdWSTRING, g_nStringIdARRAY, 10, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scm_anDataOutputNames[] = {g_nStringIdarrowheadService};

const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scm_anDataOutputTypeIds[] = {g_nStringIdArrowheadService};

const TForteInt16 FORTE_FieldsToArrowheadService::scm_anEIWithIndexes[] = {0};
const TDataIOID FORTE_FieldsToArrowheadService::scm_anEIWith[] = {0, 1, 2, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_FieldsToArrowheadService::scm_anEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FieldsToArrowheadService::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec FORTE_FieldsToArrowheadService::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  3,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

void FORTE_FieldsToArrowheadService::alg_REQ(){
CIEC_INT i;
;

i = 0;
arrowheadService().serviceDefinition() = serviceDefinition();

while((i < 10)){
// looks like while is faster than FOR when exporting to cpp

arrowheadService().interfaces()[i] = interfaces()[i];
arrowheadService().serviceMetadata()[i] = serviceMetadata()[i];
i = i+1;
}

}


void FORTE_FieldsToArrowheadService::enterStateSTART(){
  m_nECCState = scm_nStateSTART;
}

void FORTE_FieldsToArrowheadService::enterStateREQ(){
  m_nECCState = scm_nStateREQ;
  alg_REQ();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_FieldsToArrowheadService::executeEvent(TEventID pa_nEIID){
  bool bTransitionCleared;
  do{
    bTransitionCleared = true;
    switch(m_nECCState){
      case scm_nStateSTART:
        if(scm_nEventREQID == pa_nEIID)
          enterStateREQ();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateREQ:
        if(1)
          enterStateSTART();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      default:
      DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 1.", m_nECCState.operator TForteUInt16 ());
        m_nECCState = 0; //0 is always the initial state
        break;
    }
    pa_nEIID = cg_nInvalidEventID;  // we have to clear the event after the first check in order to ensure correct behavior
  }while(bTransitionCleared);
}


