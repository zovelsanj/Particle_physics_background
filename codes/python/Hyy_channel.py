import ROOT

def event_selection(tree, hist):
    Photon_1 = ROOT.TLorentzVector()
    Photon_2 = ROOT.TLorentzVector()
    n = 0
    for event in tree:
        n += 1
        ## printing the evolution in number of events
        if(n%10000==0):
            print(n)
        ## checking the trigger    
        if(tree.trigP):
            goodphoton_index = [0]*5
            goodphoton_n = 0
            photon_index = 0
            ##            
            j=0
            ## looping the photons per event
            for j in range(tree.photon_n):
                ##
                if(tree.photon_isTightID[j]):
                    ##
                    if(tree.photon_pt[j] > 25000 and (ROOT.TMath.Abs(tree.photon_eta[j]) < 2.37)\
                    and (ROOT.TMath.Abs(tree.photon_eta[j]) < 1.37 or ROOT.TMath.Abs(tree.photon_eta[j]) > 1.52)):
                        ##
                        goodphoton_n += 1  #count
                        goodphoton_index[photon_index]=j
                        photon_index += 1
                    ## end Pt and eta pre-selection
                ## end on request of quality of the photon
            ## end looping photons in the current event
                
            ## Using the two selected photons
            if(goodphoton_n==2):
                ##
                goodphoton1_index = goodphoton_index[0]
                goodphoton2_index = goodphoton_index[1]
                ## Getting couple of photons with good isolation 
                if((tree.photon_ptcone30[goodphoton1_index]/tree.photon_pt[goodphoton1_index] < 0.065)\
                and (tree.photon_etcone20[goodphoton1_index] / tree.photon_pt[goodphoton1_index] < 0.065)):
                    ##
                    if((tree.photon_ptcone30[goodphoton2_index]/tree.photon_pt[goodphoton2_index] < 0.065)\
                    and (tree.photon_etcone20[goodphoton2_index] / tree.photon_pt[goodphoton2_index] < 0.065)):
                        ##
                        Photon_1.SetPtEtaPhiE(tree.photon_pt[goodphoton1_index]/1000., tree.photon_eta[goodphoton1_index],\
                                            tree.photon_phi[goodphoton1_index],tree.photon_E[goodphoton1_index]/1000.)
                        Photon_2.SetPtEtaPhiE(tree.photon_pt[goodphoton2_index]/1000., tree.photon_eta[goodphoton2_index],\
                                            tree.photon_phi[goodphoton2_index],tree.photon_E[goodphoton2_index]/1000.)
                        ## Adding the two TLorentz vectors
                        Photon_12 = Photon_1 + Photon_2
                        ## Filling with the mass of the gamma-gamma system
                        hist.Fill(Photon_12.M())
    return hist

if __name__ == "__main__":
    root_file = ROOT.TFile.Open("../../data/data_A.GamGam.root")
    tree = root_file.Get("mini")
    print(f"Tree details: {tree.GetEntries()}")
    
    canvas = ROOT.TCanvas("Canvas","cz",800,600)
    hist = ROOT.TH1F("h_M_Hyy","Diphoton invariant-mass ; Invariant Mass m_{yy} [GeV] ; events",30,105,160)
    hist = event_selection(tree, hist)
    hist.Draw("E")
    canvas.Draw()