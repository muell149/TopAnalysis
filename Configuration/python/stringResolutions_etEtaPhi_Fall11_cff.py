import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.recoLayer0.stringResolutionProvider_cfi import *

print "*** Including object resolutions derived from Fall11 MC for:"
print "*** - electrons   - muons   - udscJetsPF     - bJetsPF     - pfMET"
print "*** Please make sure that you are really using resolutions that are suited for the objects in your analysis!"

udscResolutionPF = stringResolution.clone(parametrization = 'EtEtaPhi',
                                          functions = cms.VPSet(
    cms.PSet(
    bin = cms.string('0.000<=abs(eta) && abs(eta)<0.087'),
    et  = cms.string('et * (sqrt(0.0591^2 + (1.001/sqrt(et))^2 + (0.88/et)^2))'),
    eta  = cms.string('sqrt(0.009153^2 + (1.5112/et)^2)'),
    phi  = cms.string('sqrt(0.010049^2 + (1.6026/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.087<=abs(eta) && abs(eta)<0.174'),
    et  = cms.string('et * (sqrt(0.0619^2 + (0.975/sqrt(et))^2 + (1.54/et)^2))'),
    eta  = cms.string('sqrt(0.008875^2 + (1.5256/et)^2)'),
    phi  = cms.string('sqrt(0.009822^2 + (1.6075/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.174<=abs(eta) && abs(eta)<0.261'),
    et  = cms.string('et * (sqrt(0.05736^2 + (1.0013/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.008646^2 + (1.5395/et)^2)'),
    phi  = cms.string('sqrt(0.01011^2 + (1.5885/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.261<=abs(eta) && abs(eta)<0.348'),
    et  = cms.string('et * (sqrt(0.05685^2 + (1.0091/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00867^2 + (1.5487/et)^2)'),
    phi  = cms.string('sqrt(0.009881^2 + (1.6002/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.348<=abs(eta) && abs(eta)<0.435'),
    et  = cms.string('et * (sqrt(0.05696^2 + (1.001/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00907^2 + (1.555/et)^2)'),
    phi  = cms.string('sqrt(0.010231^2 + (1.5854/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.435<=abs(eta) && abs(eta)<0.522'),
    et  = cms.string('et * (sqrt(0.05222^2 + (1.0154/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00844^2 + (1.5859/et)^2)'),
    phi  = cms.string('sqrt(0.009819^2 + (1.6014/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.522<=abs(eta) && abs(eta)<0.609'),
    et  = cms.string('et * (sqrt(0.0502^2 + (1.0215/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00915^2 + (1.5669/et)^2)'),
    phi  = cms.string('sqrt(0.00979^2 + (1.5967/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.609<=abs(eta) && abs(eta)<0.696'),
    et  = cms.string('et * (sqrt(0.053^2 + (1.0254/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00856^2 + (1.5815/et)^2)'),
    phi  = cms.string('sqrt(0.009249^2 + (1.6224/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.696<=abs(eta) && abs(eta)<0.783'),
    et  = cms.string('et * (sqrt(0.051^2 + (1.0334/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00897^2 + (1.585/et)^2)'),
    phi  = cms.string('sqrt(0.009734^2 + (1.6132/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.783<=abs(eta) && abs(eta)<0.870'),
    et  = cms.string('et * (sqrt(0.0549^2 + (1.0362/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.0095^2 + (1.5995/et)^2)'),
    phi  = cms.string('sqrt(0.009711^2 + (1.6167/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.870<=abs(eta) && abs(eta)<0.957'),
    et  = cms.string('et * (sqrt(0.0544^2 + (1.06/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00836^2 + (1.6532/et)^2)'),
    phi  = cms.string('sqrt(0.00916^2 + (1.6407/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.957<=abs(eta) && abs(eta)<1.044'),
    et  = cms.string('et * (sqrt(0.0519^2 + (1.0943/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00782^2 + (1.6763/et)^2)'),
    phi  = cms.string('sqrt(0.00959^2 + (1.662/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.044<=abs(eta) && abs(eta)<1.131'),
    et  = cms.string('et * (sqrt(0.0539^2 + (1.1159/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.0093^2 + (1.6492/et)^2)'),
    phi  = cms.string('sqrt(0.00964^2 + (1.6732/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.131<=abs(eta) && abs(eta)<1.218'),
    et  = cms.string('et * (sqrt(0.0492^2 + (1.1562/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00986^2 + (1.695/et)^2)'),
    phi  = cms.string('sqrt(0.00969^2 + (1.7125/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.218<=abs(eta) && abs(eta)<1.305'),
    et  = cms.string('et * (sqrt(0.0489^2 + (1.1831/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.01242^2 + (1.7185/et)^2)'),
    phi  = cms.string('sqrt(0.00992^2 + (1.7573/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.305<=abs(eta) && abs(eta)<1.392'),
    et  = cms.string('et * (sqrt(0.0414^2 + (1.2451/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.01807^2 + (1.633/et)^2)'),
    phi  = cms.string('sqrt(0.01239^2 + (1.7931/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.392<=abs(eta) && abs(eta)<1.479'),
    et  = cms.string('et * (sqrt(0.0373^2 + (1.2612/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.01209^2 + (1.6927/et)^2)'),
    phi  = cms.string('sqrt(0.01348^2 + (1.8019/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.479<=abs(eta) && abs(eta)<1.566'),
    et  = cms.string('et * (sqrt(0.0125^2 + (1.2414/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.01221^2 + (1.6912/et)^2)'),
    phi  = cms.string('sqrt(0.01068^2 + (1.8512/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.566<=abs(eta) && abs(eta)<1.653'),
    et  = cms.string('et * (sqrt(0^2 + (1.083/sqrt(et))^2 + (3.06/et)^2))'),
    eta  = cms.string('sqrt(0.00975^2 + (1.6937/et)^2)'),
    phi  = cms.string('sqrt(0.00895^2 + (1.8401/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.653<=abs(eta) && abs(eta)<1.740'),
    et  = cms.string('et * (sqrt(0^2 + (1.0403/sqrt(et))^2 + (3.01/et)^2))'),
    eta  = cms.string('sqrt(0.00881^2 + (1.7054/et)^2)'),
    phi  = cms.string('sqrt(0.00902^2 + (1.8077/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.740<=abs(eta) && abs(eta)<1.830'),
    et  = cms.string('et * (sqrt(0^2 + (1.0004/sqrt(et))^2 + (3.1/et)^2))'),
    eta  = cms.string('sqrt(0.00938^2 + (1.7547/et)^2)'),
    phi  = cms.string('sqrt(0.00861^2 + (1.7858/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.830<=abs(eta) && abs(eta)<1.930'),
    et  = cms.string('et * (sqrt(0^2 + (0.9649/sqrt(et))^2 + (3.14/et)^2))'),
    eta  = cms.string('sqrt(0.00894^2 + (1.7976/et)^2)'),
    phi  = cms.string('sqrt(0.00877^2 + (1.7522/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.930<=abs(eta) && abs(eta)<2.043'),
    et  = cms.string('et * (sqrt(0^2 + (0.9244/sqrt(et))^2 + (3.142/et)^2))'),
    eta  = cms.string('sqrt(0.00893^2 + (1.8337/et)^2)'),
    phi  = cms.string('sqrt(0.00791^2 + (1.7271/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.043<=abs(eta) && abs(eta)<2.172'),
    et  = cms.string('et * (sqrt(0^2 + (0.9232/sqrt(et))^2 + (2.85/et)^2))'),
    eta  = cms.string('sqrt(0.0099^2 + (1.8166/et)^2)'),
    phi  = cms.string('sqrt(0.00775^2 + (1.7297/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.172<=abs(eta) && abs(eta)<2.322'),
    et  = cms.string('et * (sqrt(0.006^2 + (0.881/sqrt(et))^2 + (3.23/et)^2))'),
    eta  = cms.string('sqrt(0.00944^2 + (1.8015/et)^2)'),
    phi  = cms.string('sqrt(0.00807^2 + (1.7113/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.322<=abs(eta) && abs(eta)<2.500'),
    et  = cms.string('et * (sqrt(0^2 + (0.8597/sqrt(et))^2 + (3.567/et)^2))'),
    eta  = cms.string('sqrt(0.01033^2 + (2.149/et)^2)'),
    phi  = cms.string('sqrt(0.01033^2 + (1.8063/et)^2)'),
    ),
    ),
                                          constraints = cms.vdouble(0)
                                          )

bjetResolutionPF = stringResolution.clone(parametrization = 'EtEtaPhi',
                                          functions = cms.VPSet(
    cms.PSet(
    bin = cms.string('0.000<=abs(eta) && abs(eta)<0.087'),
    et  = cms.string('et * (sqrt(0.0686^2 + (1.033/sqrt(et))^2 + (1.68/et)^2))'),
    eta  = cms.string('sqrt(0.00605^2 + (1.6307/et)^2)'),
    phi  = cms.string('sqrt(0.007867^2 + (1.7398/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.087<=abs(eta) && abs(eta)<0.174'),
    et  = cms.string('et * (sqrt(0.0737^2 + (1.013/sqrt(et))^2 + (1.74/et)^2))'),
    eta  = cms.string('sqrt(0.00592^2 + (1.637/et)^2)'),
    phi  = cms.string('sqrt(0.007665^2 + (1.74/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.174<=abs(eta) && abs(eta)<0.261'),
    et  = cms.string('et * (sqrt(0.0657^2 + (1.0672/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00584^2 + (1.6471/et)^2)'),
    phi  = cms.string('sqrt(0.00755^2 + (1.7365/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.261<=abs(eta) && abs(eta)<0.348'),
    et  = cms.string('et * (sqrt(0.06198^2 + (1.0706/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00593^2 + (1.6503/et)^2)'),
    phi  = cms.string('sqrt(0.00734^2 + (1.7439/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.348<=abs(eta) && abs(eta)<0.435'),
    et  = cms.string('et * (sqrt(0.0605^2 + (1.0697/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00584^2 + (1.679/et)^2)'),
    phi  = cms.string('sqrt(0.00734^2 + (1.7548/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.435<=abs(eta) && abs(eta)<0.522'),
    et  = cms.string('et * (sqrt(0.059^2 + (1.0751/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00646^2 + (1.6689/et)^2)'),
    phi  = cms.string('sqrt(0.00767^2 + (1.7381/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.522<=abs(eta) && abs(eta)<0.609'),
    et  = cms.string('et * (sqrt(0.0577^2 + (1.0795/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00661^2 + (1.6723/et)^2)'),
    phi  = cms.string('sqrt(0.00742^2 + (1.7465/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.609<=abs(eta) && abs(eta)<0.696'),
    et  = cms.string('et * (sqrt(0.0525^2 + (1.0925/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00724^2 + (1.6538/et)^2)'),
    phi  = cms.string('sqrt(0.00771^2 + (1.733/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.696<=abs(eta) && abs(eta)<0.783'),
    et  = cms.string('et * (sqrt(0.0582^2 + (1.0858/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00763^2 + (1.6659/et)^2)'),
    phi  = cms.string('sqrt(0.00758^2 + (1.7585/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.783<=abs(eta) && abs(eta)<0.870'),
    et  = cms.string('et * (sqrt(0.0649^2 + (1.0809/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00746^2 + (1.6984/et)^2)'),
    phi  = cms.string('sqrt(0.00789^2 + (1.7527/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.870<=abs(eta) && abs(eta)<0.957'),
    et  = cms.string('et * (sqrt(0.0654^2 + (1.0976/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00807^2 + (1.703/et)^2)'),
    phi  = cms.string('sqrt(0.00802^2 + (1.7626/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.957<=abs(eta) && abs(eta)<1.044'),
    et  = cms.string('et * (sqrt(0.0669^2 + (1.107/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00843^2 + (1.7192/et)^2)'),
    phi  = cms.string('sqrt(0.0078^2 + (1.7899/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.044<=abs(eta) && abs(eta)<1.131'),
    et  = cms.string('et * (sqrt(0.0643^2 + (1.1475/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.00886^2 + (1.7425/et)^2)'),
    phi  = cms.string('sqrt(0.00806^2 + (1.8167/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.131<=abs(eta) && abs(eta)<1.218'),
    et  = cms.string('et * (sqrt(0.0645^2 + (1.1602/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.01007^2 + (1.763/et)^2)'),
    phi  = cms.string('sqrt(0.00784^2 + (1.8612/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.218<=abs(eta) && abs(eta)<1.305'),
    et  = cms.string('et * (sqrt(0.0637^2 + (1.1887/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.01272^2 + (1.778/et)^2)'),
    phi  = cms.string('sqrt(0.00885^2 + (1.9014/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.305<=abs(eta) && abs(eta)<1.392'),
    et  = cms.string('et * (sqrt(0.0695^2 + (1.2056/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.0161^2 + (1.7316/et)^2)'),
    phi  = cms.string('sqrt(0.01077^2 + (1.9319/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.392<=abs(eta) && abs(eta)<1.479'),
    et  = cms.string('et * (sqrt(0.0748^2 + (1.1985/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.01221^2 + (1.769/et)^2)'),
    phi  = cms.string('sqrt(0.01115^2 + (2.001/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.479<=abs(eta) && abs(eta)<1.566'),
    et  = cms.string('et * (sqrt(0.0624^2 + (1.2315/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.01235^2 + (1.7863/et)^2)'),
    phi  = cms.string('sqrt(0.01016^2 + (2.0217/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.566<=abs(eta) && abs(eta)<1.653'),
    et  = cms.string('et * (sqrt(0.0283^2 + (1.2534/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.01114^2 + (1.7891/et)^2)'),
    phi  = cms.string('sqrt(0.00857^2 + (2.0132/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.653<=abs(eta) && abs(eta)<1.740'),
    et  = cms.string('et * (sqrt(0.0316^2 + (1.2069/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.0106^2 + (1.8018/et)^2)'),
    phi  = cms.string('sqrt(0.00856^2 + (1.9673/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.740<=abs(eta) && abs(eta)<1.830'),
    et  = cms.string('et * (sqrt(0^2 + (1.1958/sqrt(et))^2 + (0/et)^2))'),
    eta  = cms.string('sqrt(0.01154^2 + (1.8291/et)^2)'),
    phi  = cms.string('sqrt(0.00761^2 + (1.9489/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.830<=abs(eta) && abs(eta)<1.930'),
    et  = cms.string('et * (sqrt(0^2 + (1.1409/sqrt(et))^2 + (1.7/et)^2))'),
    eta  = cms.string('sqrt(0.01203^2 + (1.875/et)^2)'),
    phi  = cms.string('sqrt(0.00721^2 + (1.9174/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.930<=abs(eta) && abs(eta)<2.043'),
    et  = cms.string('et * (sqrt(0^2 + (1.0892/sqrt(et))^2 + (2.08/et)^2))'),
    eta  = cms.string('sqrt(0.01308^2 + (1.911/et)^2)'),
    phi  = cms.string('sqrt(0.00722^2 + (1.8613/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.043<=abs(eta) && abs(eta)<2.172'),
    et  = cms.string('et * (sqrt(0^2 + (1.0899/sqrt(et))^2 + (1.63/et)^2))'),
    eta  = cms.string('sqrt(0.01337^2 + (1.9168/et)^2)'),
    phi  = cms.string('sqrt(0.00703^2 + (1.8568/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.172<=abs(eta) && abs(eta)<2.322'),
    et  = cms.string('et * (sqrt(0^2 + (1.09/sqrt(et))^2 + (1.68/et)^2))'),
    eta  = cms.string('sqrt(0.01316^2 + (1.8918/et)^2)'),
    phi  = cms.string('sqrt(0.00845^2 + (1.8568/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.322<=abs(eta) && abs(eta)<2.500'),
    et  = cms.string('et * (sqrt(0^2 + (1.1225/sqrt(et))^2 + (1.78/et)^2))'),
    eta  = cms.string('sqrt(0.01209^2 + (2.279/et)^2)'),
    phi  = cms.string('sqrt(0.00975^2 + (2.0027/et)^2)'),
    ),
    ),
                                          constraints = cms.vdouble(0)
                                          )

muonResolution   = stringResolution.clone(parametrization = 'EtEtaPhi',
                                          functions = cms.VPSet(
    cms.PSet(
    bin = cms.string('0.000<=abs(eta) && abs(eta)<0.100'),
    et  = cms.string('et * (0.005172 + 0.00014322 * et)'),
    eta  = cms.string('sqrt(0.0004332^2 + (0.00016/sqrt(et))^2 + (0.00334/et)^2)'),
    phi  = cms.string('sqrt(0^2 + (0/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.100<=abs(eta) && abs(eta)<0.200'),
    et  = cms.string('et * (0.00524 + 0.00014298 * et)'),
    eta  = cms.string('sqrt(0.0003814^2 + (0.00047/sqrt(et))^2 + (0.00259/et)^2)'),
    phi  = cms.string('sqrt(6.793e-05^2 + (0.000245/sqrt(et))^2 + (0.002741/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.200<=abs(eta) && abs(eta)<0.300'),
    et  = cms.string('et * (0.005849 + 0.0001383 * et)'),
    eta  = cms.string('sqrt(0.0003367^2 + (0.00038/sqrt(et))^2 + (0.0023/et)^2)'),
    phi  = cms.string('sqrt(0^2 + (0/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.300<=abs(eta) && abs(eta)<0.400'),
    et  = cms.string('et * (0.006497 + 0.0001331 * et)'),
    eta  = cms.string('sqrt(0.0003082^2 + (0.00017/sqrt(et))^2 + (0.00249/et)^2)'),
    phi  = cms.string('sqrt(6.59e-05^2 + (0.000301/sqrt(et))^2 + (0.002814/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.400<=abs(eta) && abs(eta)<0.500'),
    et  = cms.string('et * (0.007099 + 0.0001288 * et)'),
    eta  = cms.string('sqrt(0.00028916^2 + (0/sqrt(et))^2 + (0.002442/et)^2)'),
    phi  = cms.string('sqrt(6.27e-05^2 + (0.000359/sqrt(et))^2 + (0.002785/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.500<=abs(eta) && abs(eta)<0.600'),
    et  = cms.string('et * (0.00721 + 0.0001296 * et)'),
    eta  = cms.string('sqrt(0.0002785^2 + (0.00027/sqrt(et))^2 + (0.0026/et)^2)'),
    phi  = cms.string('sqrt(6.46e-05^2 + (0.00036/sqrt(et))^2 + (0.002845/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.600<=abs(eta) && abs(eta)<0.700'),
    et  = cms.string('et * (0.007575 + 0.0001288 * et)'),
    eta  = cms.string('sqrt(0.00028243^2 + (0/sqrt(et))^2 + (0.002887/et)^2)'),
    phi  = cms.string('sqrt(6.54e-05^2 + (0.000348/sqrt(et))^2 + (0.003013/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.700<=abs(eta) && abs(eta)<0.800'),
    et  = cms.string('et * (0.0081 + 0.000127 * et)'),
    eta  = cms.string('sqrt(0.0002652^2 + (0.000609/sqrt(et))^2 + (0.00212/et)^2)'),
    phi  = cms.string('sqrt(6.2e-05^2 + (0.000402/sqrt(et))^2 + (0.003037/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.800<=abs(eta) && abs(eta)<0.900'),
    et  = cms.string('et * (0.009156 + 0.0001312 * et)'),
    eta  = cms.string('sqrt(0.0002412^2 + (0.000678/sqrt(et))^2 + (0.00221/et)^2)'),
    phi  = cms.string('sqrt(6.26e-05^2 + (0.000458/sqrt(et))^2 + (0.003104/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.900<=abs(eta) && abs(eta)<1.000'),
    et  = cms.string('et * (0.010797 + 0.0001508 * et)'),
    eta  = cms.string('sqrt(0.0002281^2 + (0.000612/sqrt(et))^2 + (0.00245/et)^2)'),
    phi  = cms.string('sqrt(7.18e-05^2 + (0.000469/sqrt(et))^2 + (0.003307/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.000<=abs(eta) && abs(eta)<1.100'),
    et  = cms.string('et * (0.011545 + 0.0001535 * et)'),
    eta  = cms.string('sqrt(0.0002169^2 + (0.000583/sqrt(et))^2 + (0.00307/et)^2)'),
    phi  = cms.string('sqrt(6.98e-05^2 + (0.000507/sqrt(et))^2 + (0.003384/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.100<=abs(eta) && abs(eta)<1.200'),
    et  = cms.string('et * (0.013007 + 0.0001363 * et)'),
    eta  = cms.string('sqrt(0.0001954^2 + (0.000751/sqrt(et))^2 + (0.00282/et)^2)'),
    phi  = cms.string('sqrt(6.21e-05^2 + (0.000584/sqrt(et))^2 + (0.003454/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.200<=abs(eta) && abs(eta)<1.300'),
    et  = cms.string('et * (0.01443 + 0.0001308 * et)'),
    eta  = cms.string('sqrt(0.0001826^2 + (0.000838/sqrt(et))^2 + (0.00227/et)^2)'),
    phi  = cms.string('sqrt(5.37e-05^2 + (0.000667/sqrt(et))^2 + (0.00352/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.300<=abs(eta) && abs(eta)<1.400'),
    et  = cms.string('et * (0.01489 + 0.000141 * et)'),
    eta  = cms.string('sqrt(0.0001962^2 + (0.000783/sqrt(et))^2 + (0.00274/et)^2)'),
    phi  = cms.string('sqrt(5.37e-05^2 + (0.000711/sqrt(et))^2 + (0.00358/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.400<=abs(eta) && abs(eta)<1.500'),
    et  = cms.string('et * (0.01401 + 0.0001546 * et)'),
    eta  = cms.string('sqrt(0.0002004^2 + (0.000832/sqrt(et))^2 + (0.00254/et)^2)'),
    phi  = cms.string('sqrt(5.98e-05^2 + (0.000713/sqrt(et))^2 + (0.003623/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.500<=abs(eta) && abs(eta)<1.600'),
    et  = cms.string('et * (0.0132 + 0.0001687 * et)'),
    eta  = cms.string('sqrt(0.0002054^2 + (0.0007/sqrt(et))^2 + (0.00304/et)^2)'),
    phi  = cms.string('sqrt(6.21e-05^2 + (0.000781/sqrt(et))^2 + (0.003476/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.600<=abs(eta) && abs(eta)<1.700'),
    et  = cms.string('et * (0.01286 + 0.0002004 * et)'),
    eta  = cms.string('sqrt(0.0002135^2 + (0.000747/sqrt(et))^2 + (0.00319/et)^2)'),
    phi  = cms.string('sqrt(6.92e-05^2 + (0.000865/sqrt(et))^2 + (0.00337/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.700<=abs(eta) && abs(eta)<1.800'),
    et  = cms.string('et * (0.01348 + 0.0002643 * et)'),
    eta  = cms.string('sqrt(0.0002377^2 + (0.000582/sqrt(et))^2 + (0.00343/et)^2)'),
    phi  = cms.string('sqrt(9.13e-05^2 + (0.000896/sqrt(et))^2 + (0.00348/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.800<=abs(eta) && abs(eta)<1.900'),
    et  = cms.string('et * (0.0144 + 0.0003397 * et)'),
    eta  = cms.string('sqrt(0.0002628^2 + (0.000721/sqrt(et))^2 + (0.00322/et)^2)'),
    phi  = cms.string('sqrt(0.0001023^2 + (0.000994/sqrt(et))^2 + (0.00337/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.900<=abs(eta) && abs(eta)<2.000'),
    et  = cms.string('et * (0.01469 + 0.0004412 * et)'),
    eta  = cms.string('sqrt(0.0002837^2 + (0.000779/sqrt(et))^2 + (0.0031/et)^2)'),
    phi  = cms.string('sqrt(0.0001234^2 + (0.00108/sqrt(et))^2 + (0.00315/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.000<=abs(eta) && abs(eta)<2.100'),
    et  = cms.string('et * (0.01536 + 0.0006037 * et)'),
    eta  = cms.string('sqrt(0.0003156^2 + (0.00057/sqrt(et))^2 + (0.00384/et)^2)'),
    phi  = cms.string('sqrt(0.000169^2 + (0.000947/sqrt(et))^2 + (0.00422/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.100<=abs(eta) && abs(eta)<2.200'),
    et  = cms.string('et * (0.01633 + 0.000764 * et)'),
    eta  = cms.string('sqrt(0.0003526^2 + (0.00075/sqrt(et))^2 + (0.0038/et)^2)'),
    phi  = cms.string('sqrt(0.0001757^2 + (0.00116/sqrt(et))^2 + (0.00423/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.200<=abs(eta) && abs(eta)<2.300'),
    et  = cms.string('et * (0.01729 + 0.000951 * et)'),
    eta  = cms.string('sqrt(0.0004115^2 + (0.00102/sqrt(et))^2 + (0.00351/et)^2)'),
    phi  = cms.string('sqrt(0.0002071^2 + (0.001151/sqrt(et))^2 + (0.00469/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.300<=abs(eta) && abs(eta)<2.400'),
    et  = cms.string('et * (0.01753 + 0.001256 * et)'),
    eta  = cms.string('sqrt(0.0005061^2 + (0.00079/sqrt(et))^2 + (0.0045/et)^2)'),
    phi  = cms.string('sqrt(0.0002702^2 + (0.00113/sqrt(et))^2 + (0.00528/et)^2)'),
    ),
    ),
                                          constraints = cms.vdouble(0)
                                          )

elecResolution   = stringResolution.clone(parametrization = 'EtEtaPhi',
                                          functions = cms.VPSet(
    cms.PSet(
    bin = cms.string('0.000<=abs(eta) && abs(eta)<0.174'),
    et  = cms.string('et * (sqrt(0.00534^2 + (0.079/sqrt(et))^2 + (0.163/et)^2))'),
    eta  = cms.string('sqrt(0.0004522^2 + (0.00028/sqrt(et))^2 + (0.00376/et)^2)'),
    phi  = cms.string('sqrt(0.0001007^2 + (0.0011/sqrt(et))^2 + (0.00346/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.174<=abs(eta) && abs(eta)<0.261'),
    et  = cms.string('et * (sqrt(0.00518^2 + (0.0749/sqrt(et))^2 + (0.227/et)^2))'),
    eta  = cms.string('sqrt(0.0003803^2 + (0.00057/sqrt(et))^2 + (0.00276/et)^2)'),
    phi  = cms.string('sqrt(9.3e-05^2 + (0.001148/sqrt(et))^2 + (0.0035/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.261<=abs(eta) && abs(eta)<0.348'),
    et  = cms.string('et * (sqrt(0.00332^2 + (0.0879/sqrt(et))^2 + (0.12/et)^2))'),
    eta  = cms.string('sqrt(0.0003508^2 + (0/sqrt(et))^2 + (0.00324/et)^2)'),
    phi  = cms.string('sqrt(0.0001029^2 + (0.001175/sqrt(et))^2 + (0.00333/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.348<=abs(eta) && abs(eta)<0.435'),
    et  = cms.string('et * (sqrt(0.00445^2 + (0.0895/sqrt(et))^2 + (0.186/et)^2))'),
    eta  = cms.string('sqrt(0.0003191^2 + (0.00061/sqrt(et))^2 + (0.00182/et)^2)'),
    phi  = cms.string('sqrt(0.0001102^2 + (0.001148/sqrt(et))^2 + (0.00365/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.435<=abs(eta) && abs(eta)<0.522'),
    et  = cms.string('et * (sqrt(0.00453^2 + (0.0893/sqrt(et))^2 + (0.21/et)^2))'),
    eta  = cms.string('sqrt(0.0003014^2 + (0.00061/sqrt(et))^2 + (0.00146/et)^2)'),
    phi  = cms.string('sqrt(0.0001048^2 + (0.001219/sqrt(et))^2 + (0.00343/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.522<=abs(eta) && abs(eta)<0.609'),
    et  = cms.string('et * (sqrt(0.00308^2 + (0.0886/sqrt(et))^2 + (0.188/et)^2))'),
    eta  = cms.string('sqrt(0.0002966^2 + (0.000791/sqrt(et))^2 + (0/et)^2)'),
    phi  = cms.string('sqrt(0.0001019^2 + (0.001289/sqrt(et))^2 + (0.00328/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.609<=abs(eta) && abs(eta)<0.696'),
    et  = cms.string('et * (sqrt(0.00308^2 + (0.0914/sqrt(et))^2 + (0.182/et)^2))'),
    eta  = cms.string('sqrt(0.0003204^2 + (0.00033/sqrt(et))^2 + (0.00325/et)^2)'),
    phi  = cms.string('sqrt(0.0001034^2 + (0.001385/sqrt(et))^2 + (0.00253/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.696<=abs(eta) && abs(eta)<0.783'),
    et  = cms.string('et * (sqrt(0.00442^2 + (0.0914/sqrt(et))^2 + (0.231/et)^2))'),
    eta  = cms.string('sqrt(0.0003085^2 + (0.000821/sqrt(et))^2 + (0.0011/et)^2)'),
    phi  = cms.string('sqrt(0.0001147^2 + (0.00139/sqrt(et))^2 + (0.00293/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.783<=abs(eta) && abs(eta)<0.870'),
    et  = cms.string('et * (sqrt(0.00455^2 + (0.0949/sqrt(et))^2 + (0.335/et)^2))'),
    eta  = cms.string('sqrt(0.000293^2 + (0.000767/sqrt(et))^2 + (0.00211/et)^2)'),
    phi  = cms.string('sqrt(0.0001214^2 + (0.001575/sqrt(et))^2 + (0.00151/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.870<=abs(eta) && abs(eta)<0.957'),
    et  = cms.string('et * (sqrt(0.0018^2 + (0.1024/sqrt(et))^2 + (0.333/et)^2))'),
    eta  = cms.string('sqrt(0.000275^2 + (0.000765/sqrt(et))^2 + (0.00227/et)^2)'),
    phi  = cms.string('sqrt(0.000128^2 + (0.001692/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('0.957<=abs(eta) && abs(eta)<1.044'),
    et  = cms.string('et * (sqrt(0.0008^2 + (0.108/sqrt(et))^2 + (0.42/et)^2))'),
    eta  = cms.string('sqrt(0.000274^2 + (0.00062/sqrt(et))^2 + (0.00299/et)^2)'),
    phi  = cms.string('sqrt(0.0001447^2 + (0.001787/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.044<=abs(eta) && abs(eta)<1.131'),
    et  = cms.string('et * (sqrt(0.0011^2 + (0.1277/sqrt(et))^2 + (0.55/et)^2))'),
    eta  = cms.string('sqrt(0.0002694^2 + (0.000929/sqrt(et))^2 + (0.00183/et)^2)'),
    phi  = cms.string('sqrt(0.0001852^2 + (0.001817/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.131<=abs(eta) && abs(eta)<1.218'),
    et  = cms.string('et * (sqrt(0^2 + (0.1549/sqrt(et))^2 + (0.674/et)^2))'),
    eta  = cms.string('sqrt(0.0002681^2 + (0.000876/sqrt(et))^2 + (0.00234/et)^2)'),
    phi  = cms.string('sqrt(0.0001939^2 + (0.002005/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.218<=abs(eta) && abs(eta)<1.305'),
    et  = cms.string('et * (sqrt(0^2 + (0.1436/sqrt(et))^2 + (0.8/et)^2))'),
    eta  = cms.string('sqrt(0.0002584^2 + (0.000782/sqrt(et))^2 + (0.00246/et)^2)'),
    phi  = cms.string('sqrt(0.0002258^2 + (0.002064/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.305<=abs(eta) && abs(eta)<1.392'),
    et  = cms.string('et * (sqrt(0.00842^2 + (0.1175/sqrt(et))^2 + (0.951/et)^2))'),
    eta  = cms.string('sqrt(0.0002687^2 + (0.00082/sqrt(et))^2 + (0.00278/et)^2)'),
    phi  = cms.string('sqrt(0.0002467^2 + (0.00225/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.392<=abs(eta) && abs(eta)<1.479'),
    et  = cms.string('et * (sqrt(0.0068^2 + (0.144/sqrt(et))^2 + (0.892/et)^2))'),
    eta  = cms.string('sqrt(0.0002666^2 + (0.00073/sqrt(et))^2 + (0.00327/et)^2)'),
    phi  = cms.string('sqrt(0.0002337^2 + (0.002328/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.479<=abs(eta) && abs(eta)<1.653'),
    et  = cms.string('et * (sqrt(0.0245^2 + (0.196/sqrt(et))^2 + (0.555/et)^2))'),
    eta  = cms.string('sqrt(0.0002677^2 + (0.00076/sqrt(et))^2 + (0.00295/et)^2)'),
    phi  = cms.string('sqrt(0.0002498^2 + (0.00268/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.653<=abs(eta) && abs(eta)<1.740'),
    et  = cms.string('et * (sqrt(0.0174^2 + (0.127/sqrt(et))^2 + (0.894/et)^2))'),
    eta  = cms.string('sqrt(0.0002743^2 + (0/sqrt(et))^2 + (0.00435/et)^2)'),
    phi  = cms.string('sqrt(0.000284^2 + (0.002751/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.740<=abs(eta) && abs(eta)<1.830'),
    et  = cms.string('et * (sqrt(0.0144^2 + (0.133/sqrt(et))^2 + (0.708/et)^2))'),
    eta  = cms.string('sqrt(0.0002745^2 + (0.00101/sqrt(et))^2 + (0.0009/et)^2)'),
    phi  = cms.string('sqrt(0.000356^2 + (0.00279/sqrt(et))^2 + (0.0026/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.830<=abs(eta) && abs(eta)<1.930'),
    et  = cms.string('et * (sqrt(0.01492^2 + (0.126/sqrt(et))^2 + (0.596/et)^2))'),
    eta  = cms.string('sqrt(0.0002987^2 + (0.00069/sqrt(et))^2 + (0.00341/et)^2)'),
    phi  = cms.string('sqrt(0.0003468^2 + (0.002979/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('1.930<=abs(eta) && abs(eta)<2.043'),
    et  = cms.string('et * (sqrt(0.01427^2 + (0.1199/sqrt(et))^2 + (0.504/et)^2))'),
    eta  = cms.string('sqrt(0.0003285^2 + (0/sqrt(et))^2 + (0.00439/et)^2)'),
    phi  = cms.string('sqrt(0.0003017^2 + (0.003218/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.043<=abs(eta) && abs(eta)<2.172'),
    et  = cms.string('et * (sqrt(0.01619^2 + (0.097/sqrt(et))^2 + (0.483/et)^2))'),
    eta  = cms.string('sqrt(0.0003702^2 + (0/sqrt(et))^2 + (0.00447/et)^2)'),
    phi  = cms.string('sqrt(0.000287^2 + (0.003486/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.172<=abs(eta) && abs(eta)<2.322'),
    et  = cms.string('et * (sqrt(0.01223^2 + (0.1299/sqrt(et))^2 + (0.207/et)^2))'),
    eta  = cms.string('sqrt(0.0004422^2 + (0/sqrt(et))^2 + (0.00544/et)^2)'),
    phi  = cms.string('sqrt(0.000214^2 + (0.004358/sqrt(et))^2 + (0/et)^2)'),
    ),
    cms.PSet(
    bin = cms.string('2.322<=abs(eta) && abs(eta)<2.500'),
    et  = cms.string('et * (sqrt(0.0145^2 + (0.127/sqrt(et))^2 + (0.08/et)^2))'),
    eta  = cms.string('sqrt(0.000577^2 + (0.00077/sqrt(et))^2 + (0.0033/et)^2)'),
    phi  = cms.string('sqrt(8e-05^2 + (0.00525/sqrt(et))^2 + (0.0058/et)^2)'),
    ),
    ),
                                          constraints = cms.vdouble(0)
                                          )

metResolutionPF  = stringResolution.clone(parametrization = 'EtEtaPhi',
                                          functions = cms.VPSet(
    cms.PSet(
    #et  = cms.string('et * (sqrt(0.05996^2 + (20.656/et)^2)) * erf(0.10509*et)'),
    et  = cms.string('et * (sqrt(0.0337^2 + (0.888/sqrt(et))^2 + (19.552/et)^2))'),
    eta  = cms.string('sqrt(0^2 + (0/sqrt(et))^2 + (0/et)^2)'),
    phi  = cms.string('sqrt(0^2 + (1.4544/sqrt(et))^2 + (1.039/et)^2)'),
    ),
    ),
                                          constraints = cms.vdouble(0)
                                          )

