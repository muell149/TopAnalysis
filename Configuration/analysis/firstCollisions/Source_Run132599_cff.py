import FWCore.ParameterSet.Config as cms

## from /MinimumBias/Commissioning10-PromptReco-v8/RECO/
## 1547 "multijet" events in 101 files dCache at DESY

process.source.fileNames = [
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_1.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_2.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_3.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_4.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_5.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_6.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_7.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_8.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_9.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_10.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_11.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_12.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_13.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_14.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_15.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_16.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_17.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_18.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_19.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_20.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_21.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_22.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_23.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_24.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_25.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_26.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_27.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_28.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_29.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_30.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_31.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_32.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_33.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_34.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_35.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_36.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_37.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_38.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_39.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_40.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_41.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_42.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_43.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_44.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_45.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_46.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_47.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_48.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_49.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_50.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_51.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_52.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_53.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_54.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_55.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_56.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_57.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_58.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_59.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_60.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_61.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_62.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_63.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_64.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_65.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_66.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_67.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_68.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_69.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_70.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_71.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_72.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_73.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_74.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_75.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_76.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_77.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_78.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_79.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_80.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_81.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_82.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_83.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_84.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_85.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_86.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_87.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_88.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_89.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_90.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_91.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_92.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_93.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_94.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_95.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_96.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_97.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_98.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_99.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_100.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132599_101.root'
    ]
