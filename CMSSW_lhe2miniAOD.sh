# Commands for electrons
# hadronization and simulation
cmsrel CMSSW_7_1_21
cd CMSSW_7_1_21/src/
cmsenv 
cmsDriver.py Configuration/Generator/python/Hadronizer_TuneCUETP8M1_13TeV_generic_LHE_pythia8_cff.py --mc --eventcontent RAWSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1,Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM --conditions MCRUN2_71_V1::All --beamspot NominalCollision2015 --step GEN,SIM --magField 38T_PostLS1 --filein=file:/eos/uscms/store/user/zchen/HeavyB2bX/lhe/13TeV_B2bee/tran.lhe --fileout=HeavyB2bX_13TeV_TranEE_SIM.root --python_filename=HeavyB2bX_13TeV_TranEE_SIM.py -n 5

# 1st step: digitalization
cd
cmsrel CMSSW_8_0_3
cd CMSSW_8_0_3/src/
cmsenv 
cp ../../CMSSW_7_1_21/src/HeavyB2bX_13TeV_TranMuMu_SIM.* .
cmsDriver.py step1 --filein file:HeavyB2bX_13TeV_TranEE_SIM.root  --fileout file:HeavyB2bX_13TeV_TranEE_DIGI.root  --mc --eventcontent RAWSIM --pileup 2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU --datatier GEN-SIM-RAW --conditions 80X_mcRun2_asymptotic_2016_v3 --step DIGI,L1,DIGI2RAW,HLT:@frozen25ns --era Run2_25ns --customise Configuration/DataProcessing/Utils.addMonitoring -n 5

# 2nd step: Reconstruction AOD
cmsDriver.py step2 --filein file:HeavyB2bX_13TeV_TranEE_DIGI.root  --fileout file:HeavyB2bX_13TeV_TranEE_AOD.root --mc --eventcontent AODSIM,DQM --runUnscheduled --datatier AODSIM,DQMIO --conditions 80X_mcRun2_asymptotic_2016_v3 --step RAW2DIGI,L1Reco,RECO,EI,DQM:DQMOfflinePOGMC --era Run2_25ns --customise Configuration/DataProcessing/Utils.addMonitoring -n 5

# 3rd step: miniAOD
cmsDriver.py step2 --filein file:HeavyB2bX_13TeV_TranEE_AOD.root  --fileout file:HeavyB2bX_13TeV_TranEE_miniAOD.root --mc --eventcontent MINIAODSIM --runUnscheduled --datatier MINIAODSIM --conditions 80X_mcRun2_asymptotic_2016_miniAODv2_v0 --step PAT --era Run2_25ns -n 5

cmsDriver.py step2 --filein file:HeavyB2bX_13TeV_TranEE_DIGI.root  --fileout file:HeavyB2bX_13TeV_TranEE_miniAOD.root --mc --eventcontent MINIAODSIM --runUnscheduled --datatier MINIAODSIM --conditions 80X_mcRun2_asymptotic_2016_miniAODv2_v0 --step RAW2DIGI,L1Reco,RECO,EI,DQM:DQMOfflinePOGMC --era Run2_25ns --customise Configuration/DataProcessing/Utils.addMonitoring -n 5






# Commands for muons
# hadronization and simulation
cmsrel CMSSW_7_1_21
cd CMSSW_7_1_21/src/
cmsenv 
cmsDriver.py Configuration/Generator/python/Hadronizer_TuneCUETP8M1_13TeV_generic_LHE_pythia8_cff.py --mc --eventcontent RAWSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1,Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM --conditions MCRUN2_71_V1::All --beamspot NominalCollision2015 --step GEN,SIM --magField 38T_PostLS1 --filein=file:/eos/uscms/store/user/zchen/HeavyB2bX/lhe/13TeV_B2bmumu/tran.lhe --fileout=HeavyB2bX_13TeV_TranMuMu_SIM.root --python_filename=HeavyB2bX_13TeV_TranMuMu_SIM.py -n 5

# 1st step: digitalization
cd
cmsrel CMSSW_8_0_3
cd CMSSW_8_0_3/src/
cmsenv 
cp ../../CMSSW_7_1_21/src/HeavyB2bX_13TeV_TranMuMu_SIM.* .
cmsDriver.py step1 --filein file:HeavyB2bX_13TeV_TranMuMu_SIM.root  --fileout file:HeavyB2bX_13TeV_TranMuMu_DIGI.root  --mc --eventcontent RAWSIM --pileup 2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU --datatier GEN-SIM-RAW --conditions 80X_mcRun2_asymptotic_2016_v3 --step DIGI,L1,DIGI2RAW,HLT:@frozen25ns --era Run2_25ns --customise Configuration/DataProcessing/Utils.addMonitoring -n 5

# 2nd step: Reconstruction AOD
cmsDriver.py step2 --filein file:HeavyB2bX_13TeV_TranMuMu_DIGI.root  --fileout file:HeavyB2bX_13TeV_TranMuMu_AOD.root --mc --eventcontent AODSIM,DQM --runUnscheduled --datatier AODSIM,DQMIO --conditions 80X_mcRun2_asymptotic_2016_v3 --step RAW2DIGI,L1Reco,RECO,EI,DQM:DQMOfflinePOGMC --era Run2_25ns --customise Configuration/DataProcessing/Utils.addMonitoring -n 5

# 3rd step: miniAOD
cmsDriver.py step3 --filein file:HeavyB2bX_13TeV_TranMuMu_AOD.root  --fileout file:HeavyB2bX_13TeV_TranMuMu_miniAOD.root --mc --eventcontent MINIAODSIM --runUnscheduled --datatier MINIAODSIM --conditions 80X_mcRun2_asymptotic_2016_miniAODv2_v0 --step PAT --era Run2_25ns -n 5




cmsDriver.py Configuration/Generator/python/PYTHIA8_heavyB2Xb_mumu_13TeV_cff.py --mc --eventcontent RAWSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1,Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM --conditions MCRUN2_71_V1::All --beamspot NominalCollision2015 --step GEN,SIM --magField 38T_PostLS1 -n 5 --no_exec



cmsDriver.py PYTHIA8_heavyB2Xb_mumu_13TeV_cff.py --mc --eventcontent RAWSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1,Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM --conditions MCRUN2_71_V1::All --beamspot NominalCollision2015 --step GEN,SIM --magField 38T_PostLS1  -n 5 --no_exec --python_filename=HeavyB2bX_13TeV_TranMuMu_SIM.py


crab submit -c crabConfig_tutorial_MC_generation.py
crab status


./ntuple_8TeV_multicrab -c submit
'--dryrun --skip-estimates'
./ntuple_8TeV_multicrab -c proceed -w 2012_Data_Multicrab
./ntuple_8TeV_multicrab -c status -w 2012_Data_Multicrab
./ntuple_8TeV_multicrab -c resubmit -w 2012_Data_Multicrab
