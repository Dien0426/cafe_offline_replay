/* 
   ------------------
   Author: C. Yero
   
   Brief: A compilation of CaFe utility functions
   for plotting histograms / reading summary files 
   and performing numerical operations on them
   
   ------------------
*/ 

#include "../../UTILS_CAFE/UTILS/parse_utils.h"
#include "../../UTILS_CAFE/UTILS/read_csv.h"
#include "../../UTILS_CAFE/UTILS/vector_operations.h"

//___________________________________________________________________________
double get_header(string header="", string target="", string kin=""){

  /* brief: returns either total or average value (depends on column) for selected data column header from the
     cafe summary files.  The summary files are assumed to be in a fixed location and have 
     the generic format: cafe_prod_<target>_<kin>_report_summary.csv 
   
     
     ----------
     arguments:
     ----------
     header: "total_charge", "real_yield", "real_yield_err", "hms_trk_eff", "hms_trk_eff_err", "shms_trk_eff", "shms_trk_eff_err"
     target: "LD2", "Be9",  "B10",  "B11",  "C12",  "Ca40",  "Ca48",  "Fe54"
     kin:    "MF", "SRC"

   */
 
  
  // set generic .csv file name
  string file_csv = Form("summary_files_pass1/EmissCut_100MeV/cafe_prod_%s_%s_report_summary.csv", target.c_str(), kin.c_str());


 
  // return total charge (sums over charge for each run)
  if( header.compare("total_charge")==0 ){
    vector<double> v_charge         = read_csv(file_csv.c_str(), "charge"); // mC
    double charge = vsum(v_charge);
    
    return charge;
  }

  // return total yield (sums over real yield for each run)
  if( header.compare("real_yield")==0 ){
    
    vector<double> v_real_Yield     = read_csv(file_csv, "real_Yield");
    double real_Yield = vsum(v_real_Yield);
    
    return real_Yield;
  }

  // return total yield err ( root of the sum of errors ^{2} ) - basic error propagation for sum of variables  
  if( header.compare("real_yield_err")==0 ){
    
    vector<double> v_real_Yield_err = read_csv(file_csv, "real_Yield_err");
    double real_Yield_err = sqrt( vsum ( vpow(v_real_Yield_err, 2) ) ); // sqrt [  err_1^{2} + err_2^{2} + . .  . err_n^{2} ]
    
    return real_Yield_err;
    
  }

  // return weighted avg HMS tracking (and error) efficiency (presumably tracking efficiency is ~ same for every run of the same kinematic)
  if( header.compare("hms_trk_eff")==0 || header.compare("hms_trk_eff_err")==0 ){

    vector<double> v_hTrkEff        = read_csv(file_csv, "hTrkEff");
    vector<double> v_hTrkEff_err    = read_csv(file_csv, "hTrkEff_err");

    //error in weighted average is passed by reference
    double hms_trk_eff_err = 0;          

    // calculated weighted average of a vector of elements
    double hms_trk_eff              = vavgw(v_hTrkEff, v_hTrkEff_err, hms_trk_eff_err);  

    
    if( header.compare("hms_trk_eff")==0 ){
      return hms_trk_eff;
    }

    if( header.compare("hms_trk_eff_err")==0 ){
      return hms_trk_eff_err;
    }    

  }

  // return weighted avg SHMS tracking (and error) efficiency (presumably tracking efficiency is ~ same for every run of the same kinematic)
  if( header.compare("shms_trk_eff")==0 || header.compare("shms_trk_eff_err")==0 ){

    vector<double> v_pTrkEff        = read_csv(file_csv, "pTrkEff");
    vector<double> v_pTrkEff_err    = read_csv(file_csv, "pTrkEff_err");

    //error in weighted average is passed by reference
    double shms_trk_eff_err = 0;          

    // calculated weighted average of a vector of elements
    double shms_trk_eff              = vavgw(v_pTrkEff, v_pTrkEff_err, shms_trk_eff_err);  

    
    if( header.compare("shms_trk_eff")==0 ){
      return shms_trk_eff;
    }

    if( header.compare("shms_trk_eff_err")==0 ){
      return shms_trk_eff_err;
    }    

  }


  // return weighted avg total live time (presumably live time is ~ same for every run of the same kinematic)
  if( header.compare("total_live_time")==0 || header.compare("total_live_time_err")==0 ){

   
    vector<double> v_tLT            = read_csv(file_csv, "tLT");
    vector<double> v_tLT_err        = read_csv(file_csv, "tLT_err_Bi");

    //error in weighted average is passed by reference
    double total_live_time_err = 0;          

    // calculated weighted average of a vector of elements
    double total_live_time              = vavgw(v_tLT, v_tLT_err, total_live_time_err);  

    
    if( header.compare("total_live_time")==0 ){
      return total_live_time;
    }

    if( header.compare("total_live_time_err")==0 ){
      return total_live_time_err;
    }    

  }

  
  return 0;
  
}

//__________________________________________________________________
double get_param( string var="", string target="", string kin="" ){
  
  // brief: function to read parameters from the .csv files


  // set generic .csv file name
  string file_csv = Form("summary_files_pass1/EmissCut_100MeV/cafe_prod_%s_%s_report_summary.csv", target.c_str(), kin.c_str());

  // find parameters in .csv. files (usually commented lines above header in .csv file)
  
  double tgt_area_density = stod(split(FindString("target_areal_density", file_csv.c_str(), false, -1, true)[0], ':')[1]);
  double transparency     = stod(split(FindString("transparency:", file_csv.c_str(),        false, -1, true)[0], ':')[1]);

  
  //cout << Form("transparency = %.3f", transparency) << endl;
  //cout << Form("tgt_area_density = %.4f",tgt_area_density) << endl;
  
  //double Z = FindString("Z:", file_csv.c_str(), false, -1, true);
  //double N = FindString("N:", file_csv.c_str(), false, -1, true);
  //double A = FindString("A:", file_csv.c_str(), false, -1, true);

  if( var.compare("tgt_area_density")==0 ){
    return tgt_area_density;
  }

  if( var.compare("transparency")==0 ){
    return transparency;
  }


  
  return 0;
}


//____________________________________________________________________________________________________
void compare_histos( TString file1_path="path/to/file1.root", TString hist1="kin_plots/H_Pm",
		     TString file2_path="path/to/file2.root",   TString hist2="kin_plots/H_Pm",
		     TString xlabel="X-label [units]",          TString ylabel="Y-label [units]", TString title="title",
		     TString hist1_leg="hist1_legend_title", TString hist2_leg="hist2_legend_title", bool norm=true)
{

  /* brief: generic function to compare (overlay) two 1D histograms from different files (assuming they have same binning)
     
     The arguments are as follows:

     file1_path, file2_path: ROOTfile paths ( /path/to/file.root )
     hist1, hist2          : complete path to histogram objects in file (for example if they are in a sub-direcotry, then it must be specified ("path/to/hist_object")
     xlabel, ylabel, title : self-explanatory (axis labels and plot title)
     hist1_leg, hist2_leg  : histograms legend names that can help identify what the histogram being plotted is
     norm                  : boolean flag that if set to true, draws the histograms normalized to an area of 1

   */


  int font_type = 132;

  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleFont(font_type, "");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFont(font_type);
  gStyle->SetLegendTextSize(0.03);
  

  //Open  ROOT files;
  TFile *file1 = NULL;
  TFile *file2 = NULL;

  file1 = new TFile(file1_path.Data());
  file2 = new TFile(file2_path.Data());

  // declare 1D histos
  TH1F *H_hist1 = 0;  
  TH1F *H_hist2 = 0;

  // get histogram objects
  file1->cd();
  file1->GetObject(hist1.Data(), H_hist1);
  file2->cd();
  file2->GetObject(hist2.Data(), H_hist2);

  // set histos aethetics
  H_hist1->SetLineColor(kRed);
  H_hist1->SetFillColorAlpha(kRed, 0.40);
  H_hist1->SetFillStyle(3004);

  H_hist2->SetLineColor(kBlue);
  H_hist2->SetFillColorAlpha(kBlue, 0.40);
  H_hist2->SetFillStyle(3005);

  // set y-range
  H_hist1->GetYaxis()->SetRangeUser(0, H_hist1->GetMaximum()+0.6*H_hist1->GetMaximum());

  // set histogram titles/labels/font
  H_hist1->SetTitle(title);
  
  H_hist1->GetXaxis()->SetLabelSize(0.04);
  H_hist1->GetYaxis()->SetLabelSize(0.04);
  
  H_hist1->GetYaxis()->SetTitle(ylabel);
  H_hist1->GetXaxis()->SetTitle(xlabel);

  H_hist1->GetYaxis()->CenterTitle();
  H_hist1->GetXaxis()->CenterTitle();

  H_hist1->SetLabelFont(font_type, "XY");
  H_hist1->SetTitleFont(font_type, "XY");
  H_hist1->SetTitleSize(0.05, "XY");
  H_hist1->SetTitleOffset(1., "XY");


  TCanvas *c = new TCanvas("c", "c", 900, 700);

  H_hist1->Draw("histE0");
  H_hist2->Draw("sameshistE0");


  if(norm) {
    H_hist1->DrawNormalized("histE0");
    H_hist2->DrawNormalized("sameshistE0");
  }
  
  // create legend ( displays hist legend label and integral counts)
  TLegend *leg = new TLegend(0.14,0.89,0.25,0.78);
  double h1_I, h2_I;
  double h1_Ierr, h2_Ierr;
  double nbins = H_hist1->GetNbinsX();  //Get total number of bins (excluding overflow)
  h1_I = H_hist1->IntegralAndError(1, nbins, h1_Ierr);
  h2_I = H_hist2->IntegralAndError(1, nbins, h2_Ierr);
  
  leg->AddEntry(H_hist1,Form("%s | Integral: %.3f", hist1_leg.Data(), h1_I),"f");
  leg->AddEntry(H_hist2,Form("%s | Integral: %.3f", hist2_leg.Data(), h2_I));
  // draw legend
  leg->Draw();
  
  
}

//____________________________________________________________________________________________________
void compare_histos(
		    TH1F *H_hist1=0, TH1F *H_hist2 = 0, 
		    TString xlabel="X-label [units]", TString ylabel="Y-label [units]", TString title="title",
		    TString hist1_leg="hist1_legend_title", TString hist2_leg="hist2_legend_title", bool norm=true) {

  /* brief: generic function to compare (overlay) two 1D histograms (assuming they have same binning)
     (note this has the same name as function that takes file paths, this is referred to as function overloading, and allows
     the user to utilize different variations of the same function)

     The arguments are as follows:

     H_hist1, H_hist2      : pre-defined user histogram objects (must have same binning)
     xlabel, ylabel, title : self-explanatory (axis labels and plot title)
     hist1_leg, hist2_leg  : histograms legend names that can help identify what the histogram being plotted is
     norm                  : boolean flag that if set to true, draws the histograms normalized to an area of 1

   */

  gStyle->SetOptStat(0);

  int font_type = 132;

  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleFont(font_type, "");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFont(font_type);
  gStyle->SetLegendTextSize(0.03);

  // set histos aethetics
  H_hist1->SetLineColor(kRed);
  H_hist1->SetFillColorAlpha(kRed, 0.40);
  H_hist1->SetFillStyle(3004);

  H_hist2->SetLineColor(kBlue);
  H_hist2->SetFillColorAlpha(kBlue, 0.40);
  H_hist2->SetFillStyle(3005);

  // set y-range
  H_hist1->GetYaxis()->SetRangeUser(0, H_hist1->GetMaximum()+0.6*H_hist1->GetMaximum());

  // set histogram titles/labels/font
  H_hist1->SetTitle(title);
  
  H_hist1->GetXaxis()->SetLabelSize(0.04);
  H_hist1->GetYaxis()->SetLabelSize(0.04);
  
  H_hist1->GetYaxis()->SetTitle(ylabel);
  H_hist1->GetXaxis()->SetTitle(xlabel);

  H_hist1->GetYaxis()->CenterTitle();
  H_hist1->GetXaxis()->CenterTitle();

  H_hist1->SetLabelFont(font_type, "XY");
  H_hist1->SetTitleFont(font_type, "XY");
  H_hist1->SetTitleSize(0.05, "XY");
  H_hist1->SetTitleOffset(1., "XY");


  TCanvas *c = new TCanvas("c", "c", 900, 700);

  H_hist1->Draw("histE0");
  H_hist2->Draw("sameshistE0");


  if(norm) {
    H_hist1->DrawNormalized("histE0");
    H_hist2->DrawNormalized("sameshistE0");
  }
  
  // create legend ( displays hist legend label and integral counts)
  TLegend *leg = new TLegend(0.14,0.89,0.25,0.78);
  double h1_I, h2_I;
  double h1_Ierr, h2_Ierr;
  double nbins = H_hist1->GetNbinsX();  //Get total number of bins (excluding overflow)
  h1_I = H_hist1->IntegralAndError(1, nbins, h1_Ierr);
  h2_I = H_hist2->IntegralAndError(1, nbins, h2_Ierr);
  
  leg->AddEntry(H_hist1,Form("%s | Integral: %.3f", hist1_leg.Data(), h1_I),"f");
  leg->AddEntry(H_hist2,Form("%s | Integral: %.3f", hist2_leg.Data(), h2_I));
  // draw legend
  leg->Draw();

  c->Show();
  
}


//____________________________________________________________________________________________________
void overlay_nuclei(vector<string> tgt={}, vector<int> clr={}, string kin="", string hist_name="",
		    string xlabel="X-label [units]", string ylabel="Y-label [units]", string title="title"){

  /* 
     brief: cafe-specific plotting utility to overlay n nuclei histograms, assuming a generic filename that varies only with (target, kin)
     the user may change this generic file-name accordingly

     -----------
     arguments:
     -----------
     tgt {}: string vector array to hold target names (must be consistent with target as found in file name)
     clr {} : integer vector array to hold plotting colors of each target ( colors represented by integers, see https://root.cern.ch/doc/master/classTColor.html )
     kin   : single string to select kinematic setting for specified targets ("MF" or "SRC")
     hist_name : histogram object name (if histogram is in ROOT file sub-directory, then it must also be specified)
     xlabel, ylabel, title : strings to set histogram axis and title labels

     -----------------------
     example of code usage:
     -----------------------

     vector<string> tgt = {"LD2", "Be9", "B10", "B11", "C12"};
     vector<int> clr     = {2, 4, 6, 8, 9}; 
     overlay_nuclei(tgt, clr, "MF", "kin_plots/H_Pm", "Missing Momentum [GeV/c]", "Normalized Counts", "Missing Momentum (light nuclei)");
 
  */
  
  // dont show stats box
  gStyle->SetOptStat(0);

  // set global plotting style
  int font_type = 132;

  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleFont(font_type, "");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFont(font_type);
  gStyle->SetLegendTextSize(0.03);
  
  
  string fname;
  
  TCanvas *c = new TCanvas(Form("C_%s", kin.c_str()), "", 900, 700);
  TLegend *leg = new TLegend(0.14,0.89,0.25,0.70);

  // loop over each file name
  for (int i=0; i<tgt.size(); i++){

    // generic file name with specific target, kinematic
    fname = Form("analyzed_files_combined_pass1/cafe_prod_%s_%s_combined.root", tgt[i].c_str(), kin.c_str());

    
    cout << "fname = " << fname << endl;
    cout << clr[i] << endl;
    // read TFile
    TFile *file = NULL;
    file = new TFile(fname.c_str());
  
    TH1F *H_hist =0;
    
    file->cd();
    file->GetObject(hist_name.c_str(), H_hist);

    // set histos aethetics
    H_hist->SetLineColor(clr[i]);
    H_hist->SetLineWidth(2);
    H_hist->SetMarkerStyle(8);
    H_hist->SetMarkerSize(0.8);
    H_hist->SetMarkerColor(clr[i]);
	

    //H_hist->SetFillColorAlpha(clr[i], 0.40);
    //H_hist->SetFillStyle(3002);
    
    // set y-range
    H_hist->GetYaxis()->SetRangeUser(0.1, H_hist->GetMaximum()+0.6*H_hist->GetMaximum());
    
    // set histogram titles/labels/font
    H_hist->SetTitle(title.c_str());
    
    H_hist->GetXaxis()->SetLabelSize(0.04);
    H_hist->GetYaxis()->SetLabelSize(0.04);
    
    H_hist->GetYaxis()->SetTitle(ylabel.c_str());
    H_hist->GetXaxis()->SetTitle(xlabel.c_str());
    
    H_hist->GetYaxis()->CenterTitle();
    H_hist->GetXaxis()->CenterTitle();
    
    H_hist->SetLabelFont(font_type, "XY");
    H_hist->SetTitleFont(font_type, "XY");
    H_hist->SetTitleSize(0.05, "XY");
    H_hist->SetTitleOffset(1., "XY");
    H_hist->SetStats(0);
    // changed to canvas and draw
    c->cd();
    if(tgt.size()==1) { H_hist->DrawNormalized("histE0") ;}
    else{
      H_hist->DrawNormalized("sameshistE0");
    }

    // add legend entry
    leg->AddEntry(H_hist,Form("%s %s", tgt[i].c_str(), kin.c_str()),"f");

  }

  leg->Draw();
  
}



//_______________________________________________________________________________________________
vector<TH1F*> get_single_ratios(string tgtA="",  string kinA="", string tgtB="", string kinB="",
				string hist_name="",  bool show_histos=false ){
  
  // brief: calculate single ratios of binned histograms (hist_name) for  target, kinematics): R = tgtA_kinA / tgtB_kinB  
  // using the analyzed CaFe *_combined.root files .  Example:  Ca48 MF / Ca40 MF,  Fe54 SRC / Ca48 SRC, etc.


  
  // define histogram scale variables 
  double scale_factor_A,  Q_A,  hms_trk_eff_A,  shms_trk_eff_A,  total_LT_A;
  double scale_factor_B, Q_B, hms_trk_eff_B, shms_trk_eff_B, total_LT_B;

  
  // get info from summary files (for scaling histograms)
  Q_A  = get_header("total_charge", tgtA.c_str(),  kinA.c_str());    
  Q_B = get_header("total_charge", tgtB.c_str(),  kinB.c_str());
  
  hms_trk_eff_A    = get_header("hms_trk_eff",  tgtA.c_str(), kinA.c_str() );
  hms_trk_eff_B   = get_header("hms_trk_eff",  tgtB.c_str(), kinB.c_str() );    
  
  shms_trk_eff_A   = get_header("shms_trk_eff", tgtA.c_str(), kinA.c_str() );
  shms_trk_eff_B  = get_header("shms_trk_eff", tgtB.c_str(), kinB.c_str() );
  
  total_LT_A       = get_header("total_live_time", tgtA.c_str(),  kinA.c_str());
  total_LT_B      = get_header("total_live_time", tgtB.c_str(),  kinB.c_str());
  
  scale_factor_A   = 1. / ( Q_A * hms_trk_eff_A * shms_trk_eff_A * total_LT_A ) ;
  scale_factor_B   = 1. / ( Q_B * hms_trk_eff_B * shms_trk_eff_B * total_LT_B ) ;
  
  // set .root file names 
  string fname_A = Form("analyzed_files_combined_pass1/cafe_prod_%s_%s_combined.root", tgtA.c_str(), kinA.c_str());
  string fname_B = Form("analyzed_files_combined_pass1/cafe_prod_%s_%s_combined.root", tgtB.c_str(), kinB.c_str());

  // define TFile
  TFile *file_A  = NULL;
  TFile *file_B = NULL;
    
  
  TH1F *H_hist_A  = 0;  
  TH1F *H_hist_B = 0;
  //TH1F *H_hist_R = 0;
    
  // read TFile
  file_A = new TFile(fname_A.c_str());
  file_B = new TFile(fname_B.c_str());

   
  // get histogram objects
  file_A->cd(); 
  file_A->GetObject(hist_name.c_str(), H_hist_A);

  // scale histogram appropiately
  H_hist_A->Scale(scale_factor_A);
  
    
  file_B->cd();
  file_B->GetObject(hist_name.c_str(), H_hist_B);

  // scale histogram appropiately
  H_hist_B->Scale(scale_factor_B);
  

  // calculate the ratio (A * scale_factor / (B * scale_factor) )
  TH1F *H_hist_R = (TH1F*)H_hist_A->Clone("H_hist_R");
  H_hist_R->Divide(H_hist_A, H_hist_B);

  if(show_histos) {

    int font_type = 132;
    gStyle->SetTitleFontSize(0.07);
    gStyle->SetTitleFont(font_type, "");
    gStyle->SetLegendBorderSize(0);
    gStyle->SetLegendFont(font_type);
    gStyle->SetLegendTextSize(0.05);
  
    // set histos aethetics
  H_hist_A->SetLineColor(kRed);
  H_hist_A->SetFillColorAlpha(kRed, 0.40);
  H_hist_A->SetFillStyle(3004);

  H_hist_B->SetLineColor(kBlue);
  H_hist_B->SetFillColorAlpha(kBlue, 0.40);
  H_hist_B->SetFillStyle(3005);

  H_hist_R->SetLineColor(kBlack);
  H_hist_R->SetFillColorAlpha(kBlack, 0.40);
  H_hist_R->SetFillStyle(3005);
  
  // set histogram titles/labels/font
  H_hist_A->SetTitle(H_hist_A->GetTitle());
  
  H_hist_A->GetXaxis()->SetLabelSize(0.04);
  H_hist_A->GetYaxis()->SetLabelSize(0.04);

  H_hist_A->SetLabelFont(font_type, "XY");
  
  H_hist_R->SetLabelFont(font_type, "XY");
  H_hist_R->GetXaxis()->SetLabelSize(0.04);
  H_hist_R->GetYaxis()->SetLabelSize(0.04);
  H_hist_R->SetMarkerStyle(8);
  H_hist_R->SetMarkerSize(0.8);
  H_hist_R->SetMarkerColor(kBlack);

  // set histos proper names
  H_hist_A->SetName(Form("%s_%s", tgtA.c_str(), kinA.c_str()));
  H_hist_B->SetName(Form("%s_%s", tgtB.c_str(), kinB.c_str()));
  H_hist_R->SetName(Form("Ratio %s%s/%s%s", tgtA.c_str(), kinA.c_str(), tgtB.c_str(), kinB.c_str()));

     
    TCanvas *c = new TCanvas("c", "", 800,1200);
    c->Divide(1,2);

    c->cd(1);
    H_hist_A->SetStats(0);
    H_hist_B->SetStats(0);
    H_hist_A->Draw("histE0");
    H_hist_B->Draw("sameshistE0");
  
    // create legend ( displays hist legend label and integral counts)
    TLegend *leg1 = new TLegend(0.14,0.89,0.25,0.65);
    double h1_I, h2_I;
    double h1_Ierr, h2_Ierr;
    double nbins = H_hist_A->GetNbinsX();  //Get total number of bins (excluding overflow)
    h1_I = H_hist_A->IntegralAndError(1, nbins, h1_Ierr);
    h2_I = H_hist_B->IntegralAndError(1, nbins, h2_Ierr);
    
    leg1->AddEntry(H_hist_A,Form("#splitline{%s %s}{Integral: %.3f #pm %.2f}", tgtA.c_str(), kinA.c_str(), h1_I, h1_Ierr), "f");
    leg1->AddEntry(H_hist_B,Form("#splitline{%s %s}{Integral: %.3f #pm %.2f}", tgtB.c_str(), kinB.c_str(), h2_I, h2_Ierr), "f");
    // draw legend
    leg1->Draw();

    c->cd(2);


    H_hist_R->SetStats("n");
    H_hist_R->Draw();


  }
  
  // save histograms to a vector to be returned to the user
 
  vector<TH1F*> hvec;
  

  hvec.push_back(H_hist_A);
  hvec.push_back(H_hist_B);
  hvec.push_back(H_hist_R);

  
  return hvec;

  
}





