void test(){
 
TFile *temp = new TFile("test.root", "RECREATE");

 float inix= 0;
 float finx= 60;
 float nbinx= 60.0; 
 
//TFile * fD = new TFile("/afs/cern.ch/user/q/quwang/work/RunII/CMSSW_7_4_3/src/ExoDiBosonResonances/EDBRTreeMaker/test/15Spring_50ns/SingleMuon.root");
//TFile * fD = new TFile("pileupDATA.root");
TFile * fD = new TFile("/afs/cern.ch/user/q/quwang/work/Samples/singleEl15Dv4.root");
//TFile * fD = new TFile("/afs/cern.ch/user/q/quwang/work/Samples/singleMuon15Dv4.root");
//TFile * fD = new TFile("/afs/cern.ch/user/q/quwang/work/Samples/biasXsec_72000.root"); //singleMuon15Dv4.root");
TTree * tree = (TTree *)fD->Get("treeDumper/EDBRCandidates");
int nVtx;
tree->SetBranchAddress("nVtx", &nVtx);

Long64_t nentries = tree->GetEntriesFast();
//TFIle->Data;
//TH1D *hD = (TH1D *)fD->Get("pileup");
//TH1D *hRatio= (TH1D *)fD->Get("pileup");
// hD->Sumw2();
// hRatio->Sumw2();

 TH1D *hD= new TH1D("hD","h500",nbinx,inix,finx);
TH1D *hRatio= new TH1D("hRatio","hRatio500",nbinx,inix,finx);
 hD->Sumw2();
 hRatio->Sumw2();
for(int i2=0; i2<= nentries; i2++)
{
    tree->GetEntry(i2);

    //if(nVtx>-0.1){
       hD->Fill(nVtx); 
       hRatio->Fill(nVtx);
    //} 
 }

cout<< "nDCount: " << endl;
double nDError;
cout<< "nDCount1: " << endl;
double nDCount = hRatio->IntegralAndError(1,50,nDError);
cout<< "nDCount: " << nDCount<<"nDError: "<<nDError<<endl;

nDCount = hRatio->IntegralAndError(1,50,nDError);
cout<< "nDCount: " << nDCount<<"nDError: "<<nDError<<endl;

//TFile * fMC = new TFile("/afs/cern.ch/user/q/quwang/work/RunII/CMSSW_7_4_3/src/ExoDiBosonResonances/EDBRTreeMaker/test/15Spring_50ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
//TFile * fMC = new TFile("pileupMC.root");
TFile * fMC = new TFile("/afs/cern.ch/user/q/quwang/work/Samples/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
//TFile * fMC = new TFile("/afs/cern.ch/user/q/quwang/work/Samples/allback_W_T.root");//WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
//TFile * fMC = new TFile("/afs/cern.ch/user/q/quwang/work/Samples/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
TTree * treeMC = (TTree *)fMC->Get("treeDumper/EDBRCandidates");
treeMC->SetBranchAddress("nVtx", &nVtx);
Long64_t nentriesMC = treeMC->GetEntriesFast();
TH1D *h1= new TH1D("h1","h500",nbinx,inix,finx);
h1->Sumw2();
for(int i=0; i<= nentriesMC; i++)
{
    treeMC->GetEntry(i);
    h1->Fill(nVtx);
    //if(nVtx>-0.1) h1->Fill(nVtx);
}
/*TFile * fMC1 = new TFile("/afs/cern.ch/user/q/quwang/work/Samples/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
TTree * treeMC1 = (TTree *)fMC1->Get("treeDumper/EDBRCandidates");
treeMC1->SetBranchAddress("nVtx", &nVtx);
Long64_t nentriesMC1 = treeMC1->GetEntriesFast();
TH1D *h2= new TH1D("h2","h500",nbinx,inix,finx);
h2->Sumw2();
for(int i=0; i<= nentriesMC1; i++)
{
    treeMC1->GetEntry(i);
    h2->Fill(nVtx);
    //if(nVtx>-0.1) h2->Fill(nVtx);
}
THStack* hs = new THStack("hs", "Run2 @13TeV");
hs->Add(h1);
hs->Add(h2);
*/
double n1Error;
//double n1Count = hs->IntegralAndError(1,nbinx-1,n1Error);
double n1Count = h1->IntegralAndError(1,50,n1Error);
cout<<"n1Count: "<<n1Count<<"n1Error: "<<n1Error<<endl;

//TH1D * hRatio = (TH1D *) hD -> Clone("Ratio");
//TH1D * hRatio = (TH1D *) hD -> Clone("Ratio");
//hRatio->Sumw2();
//hRatio->Scale(n1Count/nDCount);
hRatio->Scale(n1Count/nDCount);
//hRatio->Divide(hs);  
hRatio->Divide(h1);  
 

temp->cd();
hRatio->Write();
temp->Close();
delete temp;

/*
TFIle->MCttbar
  
TH1D *h1= new TH1D("h1","h500",nbinx,inix,finx);
h1->Sumw2();

double n1Error;
double n1Count = h1->IntegralAndError(0,nbin+?,n1Error);
cout<<n1Count<<"   "<<n1Error<<endl;


for(int i=0; i<=numberOfEntries-1; i++)
{
    h1->Fill(nPV); 
}

 
 TH1D * hRatio = (TH1D *) hD -> Clone("Ratio");
 hRatio->Sumw2();
 hRatio->Scale(n1Count/nDCount);
 hRatio->Divide(h1);  
 

        temp->cd();
        hRatio->Write();
        temp->Close();
        delete temp;
*/
}
