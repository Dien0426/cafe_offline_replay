import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sys
import uncertainties
from uncertainties import ufloat
from uncertainties import unumpy


def get_data(header='', fname=''):

    # read any data from the .csv file
    
    # read .csv file
    df = pd.read_csv(fname, comment='#')
    
    # sort from small to larger beam current (for normalizing purposes) 
    df = df.sort_values(by=['avg_current'])

    #print(df)
    data_array = np.array(df[header])

    return data_array
    
'''
def make_plots():

    print('Calling make_plots()')

    I_be9_mf             = get_data('Be9', 'MF', 'avg_current')
    Q_be9_mf             = get_data('Be9', 'MF', 'charge')
    N_be9_mf             = unumpy.uarray(get_data('Be9', 'MF', 'real_Yield'),  get_data('Be9', 'MF', 'real_Yield_err') )
    hms_trk_eff_be9_mf   = unumpy.uarray(get_data('Be9', 'MF', 'hTrkEff'),     get_data('Be9', 'MF', 'hTrkEff_err') )
    shms_trk_eff_be9_mf  = unumpy.uarray(get_data('Be9', 'MF', 'pTrkEff'),     get_data('Be9', 'MF', 'pTrkEff_err') )
    total_LT_be9_mf      = unumpy.uarray(get_data('Be9', 'MF', 'tLT'),         get_data('Be9', 'MF', 'tLT_err_Bi') )
    mult_trk_eff_be9_mf  = np.array(get_data('Be9', 'MF', 'multi_track_eff') )
    Y_be9_mf = N_be9_mf / ( Q_be9_mf * hms_trk_eff_be9_mf * shms_trk_eff_be9_mf * total_LT_be9_mf * mult_trk_eff_be9_mf)              
    relY_be9_mf  = Y_be9_mf / Y_be9_mf[0] 

    I_b10_mf             = get_data('B10', 'MF', 'avg_current')
    Q_b10_mf             = get_data('B10', 'MF', 'charge')
    N_b10_mf             = unumpy.uarray(get_data('B10', 'MF', 'real_Yield'),  get_data('B10', 'MF', 'real_Yield_err') )
    hms_trk_eff_b10_mf   = unumpy.uarray(get_data('B10', 'MF', 'hTrkEff'),     get_data('B10', 'MF', 'hTrkEff_err') )
    shms_trk_eff_b10_mf  = unumpy.uarray(get_data('B10', 'MF', 'pTrkEff'),     get_data('B10', 'MF', 'pTrkEff_err') )
    total_LT_b10_mf      = unumpy.uarray(get_data('B10', 'MF', 'tLT'),         get_data('B10', 'MF', 'tLT_err_Bi') )
    mult_trk_eff_b10_mf  = np.array(get_data('B10', 'MF', 'multi_track_eff') )
    Y_b10_mf = N_b10_mf / ( Q_b10_mf * hms_trk_eff_b10_mf * shms_trk_eff_b10_mf * total_LT_b10_mf * mult_trk_eff_b10_mf)              
    relY_b10_mf  = Y_b10_mf / Y_b10_mf[0]

    I_b11_mf             = get_data('B11', 'MF', 'avg_current')
    Q_b11_mf             = get_data('B11', 'MF', 'charge')
    N_b11_mf             = unumpy.uarray(get_data('B11', 'MF', 'real_Yield'),  get_data('B11', 'MF', 'real_Yield_err') )
    hms_trk_eff_b11_mf   = unumpy.uarray(get_data('B11', 'MF', 'hTrkEff'),     get_data('B11', 'MF', 'hTrkEff_err') )
    shms_trk_eff_b11_mf  = unumpy.uarray(get_data('B11', 'MF', 'pTrkEff'),     get_data('B11', 'MF', 'pTrkEff_err') )
    total_LT_b11_mf      = unumpy.uarray(get_data('B11', 'MF', 'tLT'),         get_data('B11', 'MF', 'tLT_err_Bi') )
    mult_trk_eff_b11_mf  = np.array(get_data('B11', 'MF', 'multi_track_eff') )
    Y_b11_mf = N_b11_mf / ( Q_b11_mf * hms_trk_eff_b11_mf * shms_trk_eff_b11_mf * total_LT_b11_mf * mult_trk_eff_b11_mf)              
    relY_b11_mf  = Y_b11_mf / Y_b11_mf[1]

    I_c12_mf             = get_data('C12', 'MF', 'avg_current')
    Q_c12_mf             = get_data('C12', 'MF', 'charge')
    N_c12_mf             = unumpy.uarray(get_data('C12', 'MF', 'real_Yield'),  get_data('C12', 'MF', 'real_Yield_err') )
    hms_trk_eff_c12_mf   = unumpy.uarray(get_data('C12', 'MF', 'hTrkEff'),     get_data('C12', 'MF', 'hTrkEff_err') )
    shms_trk_eff_c12_mf  = unumpy.uarray(get_data('C12', 'MF', 'pTrkEff'),     get_data('C12', 'MF', 'pTrkEff_err') )
    total_LT_c12_mf      = unumpy.uarray(get_data('C12', 'MF', 'tLT'),         get_data('C12', 'MF', 'tLT_err_Bi') )
    mult_trk_eff_c12_mf  = np.array(get_data('C12', 'MF', 'multi_track_eff') )
    Y_c12_mf = N_c12_mf / ( Q_c12_mf * hms_trk_eff_c12_mf * shms_trk_eff_c12_mf * total_LT_c12_mf * mult_trk_eff_c12_mf)              
    relY_c12_mf  = Y_c12_mf[-4:] / (Y_c12_mf[-4:])[1]
    
    # -------------
    # heavy nuclei
    #--------------
    I_ca40_mf             = get_data('Ca40', 'MF', 'avg_current')
    Q_ca40_mf             = get_data('Ca40', 'MF', 'charge')
    N_ca40_mf             = unumpy.uarray(get_data('Ca40', 'MF', 'real_Yield'),  get_data('Ca40', 'MF', 'real_Yield_err') )
    hms_trk_eff_ca40_mf   = unumpy.uarray(get_data('Ca40', 'MF', 'hTrkEff'),     get_data('Ca40', 'MF', 'hTrkEff_err') )
    shms_trk_eff_ca40_mf  = unumpy.uarray(get_data('Ca40', 'MF', 'pTrkEff'),     get_data('Ca40', 'MF', 'pTrkEff_err') )
    total_LT_ca40_mf      = unumpy.uarray(get_data('Ca40', 'MF', 'tLT'),         get_data('Ca40', 'MF', 'tLT_err_Bi') )
    mult_trk_eff_ca40_mf  = np.array(get_data('Ca40', 'MF', 'multi_track_eff') )
    Y_ca40_mf = N_ca40_mf / ( Q_ca40_mf * hms_trk_eff_ca40_mf * shms_trk_eff_ca40_mf * total_LT_ca40_mf * mult_trk_eff_ca40_mf)              
    relY_ca40_mf  = Y_ca40_mf / Y_ca40_mf[0]  

    I_ca48_mf             = get_data('Ca48', 'MF', 'avg_current')
    Q_ca48_mf             = get_data('Ca48', 'MF', 'charge')
    T2_scl_ca48_mf        = get_data('Ca48', 'MF', 'T2_scl_rate') * 1000. * get_data('Ca48', 'MF', 'beam_time')
    N_ca48_mf             = unumpy.uarray(get_data('Ca48', 'MF', 'real_Yield'),  get_data('Ca48', 'MF', 'real_Yield_err') )
    hms_trk_eff_ca48_mf   = unumpy.uarray(get_data('Ca48', 'MF', 'hTrkEff'),     get_data('Ca48', 'MF', 'hTrkEff_err') )
    shms_trk_eff_ca48_mf  = unumpy.uarray(get_data('Ca48', 'MF', 'pTrkEff'),     get_data('Ca48', 'MF', 'pTrkEff_err') )
    total_LT_ca48_mf      = unumpy.uarray(get_data('Ca48', 'MF', 'tLT'),         get_data('Ca48', 'MF', 'tLT_err_Bi') )
    mult_trk_eff_ca48_mf  = np.array(get_data('Ca48', 'MF', 'multi_track_eff') )
    Y_ca48_mf = N_ca48_mf / ( Q_ca48_mf * hms_trk_eff_ca48_mf * shms_trk_eff_ca48_mf * total_LT_ca48_mf * mult_trk_eff_ca48_mf)              
    relY_ca48_mf  = Y_ca48_mf[-3:] / (Y_ca48_mf[-3:])[0]
    T2_scl_norm_ca48_mf = T2_scl_ca48_mf / Q_ca48_mf
    relT2_ca48_mf = T2_scl_norm_ca48_mf[-3:]  / (T2_scl_norm_ca48_mf[-3:])[0] 

    I_fe54_mf             = get_data('Fe54', 'MF', 'avg_current')
    Q_fe54_mf             = get_data('Fe54', 'MF', 'charge')
    N_fe54_mf             = unumpy.uarray(get_data('Fe54', 'MF', 'real_Yield'),  get_data('Fe54', 'MF', 'real_Yield_err') )
    hms_trk_eff_fe54_mf   = unumpy.uarray(get_data('Fe54', 'MF', 'hTrkEff'),     get_data('Fe54', 'MF', 'hTrkEff_err') )
    shms_trk_eff_fe54_mf  = unumpy.uarray(get_data('Fe54', 'MF', 'pTrkEff'),     get_data('Fe54', 'MF', 'pTrkEff_err') )
    total_LT_fe54_mf      = unumpy.uarray(get_data('Fe54', 'MF', 'tLT'),         get_data('Fe54', 'MF', 'tLT_err_Bi') )
    mult_trk_eff_fe54_mf  = np.array(get_data('Fe54', 'MF', 'multi_track_eff') )
    Y_fe54_mf = N_fe54_mf / ( Q_fe54_mf * hms_trk_eff_fe54_mf * shms_trk_eff_fe54_mf * total_LT_fe54_mf * mult_trk_eff_fe54_mf)              
    relY_fe54_mf  = Y_fe54_mf / Y_fe54_mf[0]  

    plt.subplot(1, 2, 1)
    #plt.errorbar(I_be9_mf,       unumpy.nominal_values(Y_be9_mf)/Y_be9_mf[0].n,             unumpy.std_devs(Y_be9_mf)/Y_be9_mf[0].n,             marker='o',markersize=8, color='r', mec='k', linestyle='dashed', label='Be9 MF (yield)')
    #plt.errorbar(I_b10_mf,       unumpy.nominal_values(Y_b10_mf)/Y_b10_mf[0].n,             unumpy.std_devs(Y_b10_mf)/Y_b10_mf[0].n,             marker='o',markersize=8, color='b', mec='k', linestyle='dashed', label='B10 MF (yield)')
    #plt.errorbar(I_b11_mf,       unumpy.nominal_values(Y_b11_mf)/Y_b11_mf[1].n,             unumpy.std_devs(Y_b11_mf)/Y_b11_mf[1].n,             marker='o',markersize=8, color='g', mec='k', linestyle='dashed', label='B11 MF (yield)')
    #plt.errorbar(I_c12_mf[-4:],       unumpy.nominal_values(Y_c12_mf[-4:])/(Y_c12_mf[-4:])[1].n,             unumpy.std_devs(Y_c12_mf[-4:])/(Y_c12_mf[-4:])[1].n,             marker='o',markersize=8, color='darkorange', mec='k', linestyle='dashed', label='C12 MF (yield)')

    print('I_c12_mf -->',I_c12_mf)
    print('Y_c12_mf --->', unumpy.nominal_values(Y_c12_mf))
    print('T2_scl_rate_norm_ca48_mf[-3:]-->',T2_scl_norm_ca48_mf[-3:])
    plt.legend()

    
    plt.subplot(1, 2, 2)
    plt.errorbar(I_ca48_mf[-3:],  unumpy.nominal_values(Y_ca48_mf[-3:])/(Y_ca48_mf[-3:])[0].n, unumpy.std_devs(Y_ca48_mf[-3:])/(Y_ca48_mf[-3:])[0].n, marker='o',markersize=8, color='magenta', mec='k', linestyle='dashed', label='Ca48 MF (yield)')
    plt.plot(I_ca48_mf[-3:],  T2_scl_norm_ca48_mf[-3:]/(T2_scl_norm_ca48_mf[-3:])[0], marker='o',markersize=8, color='magenta', mec='k', linestyle='solid', label='Ca48 MF (T2 e- scalers)')
    
    plt.errorbar(I_ca40_mf,       unumpy.nominal_values(Y_ca40_mf)/Y_ca40_mf[0].n,             unumpy.std_devs(Y_ca40_mf)/Y_ca40_mf[0].n,             marker='o',markersize=8, color='darkorange', mec='k', linestyle='dashed', label='Ca40 MF (yield)')
    plt.errorbar(I_fe54_mf,       unumpy.nominal_values(Y_fe54_mf)/Y_fe54_mf[1].n,             unumpy.std_devs(Y_fe54_mf)/Y_fe54_mf[1].n,             marker='o',markersize=8, color='gold', mec='k', linestyle='dashed', label='Fe54 MF (yield)')

    plt.ylim(0.9, 1.07)

    plt.legend()
    plt.show()
    #print(relY_ca48_mf)
    #print(Y[-3:]/(Y[-3:])[0])
    #print(unumpy.nominal_values(Y)[-3:])
    #print(unumpy.std_devs(Y)[-3:])
'''


def get_relative(name='',  file1=''):

    # name: 'rel_yield_nom', 'rel_yield_err', 'rel_T2_nom', 'rel_T2_err'
    
    # get relevant header info (from file1)
    I                    = get_data('avg_current', file1 )
    Q                    = get_data('charge', file1)
    T2_scl               = get_data('T2_scl_rate', file1) * 1000. * get_data('beam_time', file1) #[kHz] * 1000 Hz/1kHz [sec] = [counts] 

    N                    = unumpy.uarray(get_data('real_Yield', file1),  get_data('real_Yield_err', file1) )
    hms_trk_eff   = unumpy.uarray(get_data('hTrkEff',    file1),  get_data('hTrkEff_err',    file1) )
    shms_trk_eff  = unumpy.uarray(get_data('pTrkEff',    file1),  get_data('pTrkEff_err',    file1) )
    total_LT      = unumpy.uarray(get_data('tLT',        file1),  get_data('tLT_err_Bi',     file1) )
    mult_trk_eff  = np.array(get_data('multi_track_eff', file1) )
    
    # calcualte charge-normalized yield
    Y     = N / ( Q * hms_trk_eff * shms_trk_eff * total_LT * mult_trk_eff)              
    relY  = Y / Y[0] 

    Y_nom = unumpy.nominal_values(Y)
    Y_err = unumpy.std_devs(Y)

    relY_nom = unumpy.nominal_values(relY)
    relY_err = unumpy.std_devs(relY)
    
    #calculate T2 scaler counts / charge
    T2    = T2_scl/Q 
    relT2 = T2/T2[0]

    T2_nom = unumpy.nominal_values(T2)
    T2_err = unumpy.std_devs(T2)
    
    relT2_nom = unumpy.nominal_values(relT2)
    relT2_err = unumpy.std_devs(relT2)

    if(name=='rel_yield_nom'):
        return relY_nom
    elif(name=='rel_yield_err'):
        return relY_err
    elif(name=='rel_T2_nom'):
        return relT2_nom
    elif(name=='rel_T2_err'):
        return relT2_err

def compare():
    
    # Brief: this method is used to compare changes in the relative charge-norm yield
    # for a given target, for various studies done. Additional studies can be added, bu
    # then the overlay can get a little bit crowded.  converntion: use file1 for new, and file2 for existing

    target='Au197'
    file_arr= [ '../../summary_files/rate_dependence_study/phase3/cafe_prod_%s_MF_report_summary.csv'%(target),
                '../../summary_files/rate_dependence_study/phase2/cafe_prod_%s_MF_report_summary.csv'%(target),
                '../../summary_files/rate_dependence_study/phase1/cafe_prod_%s_MF_report_summary.csv'%(target),
                '../../summary_files/rate_dependence_study/phase0/cafe_prod_%s_MF_report_summary.csv'%(target) ]

    imarker = ['v', '^', 's', 'o']
    icolor  = ['g', 'b', 'gray', 'k']
    
    fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(8, 4))

    for i, ifile in enumerate(file_arr):
    
        # get relevant header info (from ifile)
        I_f1                    = get_data('avg_current', ifile )
        Q_f1                    = get_data('charge', ifile)
        T2_scl_rate_f1          = get_data('T2_scl_rate', ifile)
        T2_scl_f1               = get_data('T2_scl_rate', ifile) * 1000. * get_data('beam_time', ifile) #[kHz] * 1000 Hz/1kHz [sec] = [counts] 
        N_f1                    = unumpy.uarray(get_data('real_Yield', ifile),  get_data('real_Yield_err', ifile) )
        hms_trk_eff_f1   = unumpy.uarray(get_data('hTrkEff',    ifile),  get_data('hTrkEff_err',    ifile) )
        shms_trk_eff_f1  = unumpy.uarray(get_data('pTrkEff',    ifile),  get_data('pTrkEff_err',    ifile) )
        total_LT_f1      = unumpy.uarray(get_data('tLT',        ifile),  get_data('tLT_err_Bi',     ifile) )
        mult_trk_eff_f1  = np.array(get_data('multi_track_eff', ifile) )
        
        # calcualte charge-normalized yield
        Y_f1     = N_f1 / ( Q_f1 * hms_trk_eff_f1 * shms_trk_eff_f1 * total_LT_f1 * mult_trk_eff_f1)              
        relY_f1  = Y_f1 / Y_f1[0] 
        
        Y_f1_nom = unumpy.nominal_values(Y_f1)
        Y_f1_err = unumpy.std_devs(Y_f1)
        
        relY_f1_nom = unumpy.nominal_values(relY_f1)
        relY_f1_err = unumpy.std_devs(relY_f1)
        
        #calculate T2 scaler counts / charge
        T2_f1    = T2_scl_f1/Q_f1 
        relT2_f1 = T2_f1/T2_f1[0]
        
        T2_f1_nom = unumpy.nominal_values(T2_f1)
        T2_f1_err = unumpy.std_devs(T2_f1)
        
        relT2_f1_nom = unumpy.nominal_values(relT2_f1)
        relT2_f1_err = unumpy.std_devs(relT2_f1)
        
        print('relY_f1_nom=',relY_f1_nom)
        print('relY_f1_err=',relY_f1_err)

        total_LT_nom = unumpy.nominal_values(total_LT_f1 )
        total_LT_err = unumpy.std_devs(total_LT_f1 )
        
        plt.subplot(1, 2, 1)
        #plot relative yield for files 1, 2
        #plt.errorbar(I_f1, relY_f1_nom, relY_f1_err,   marker=imarker[i], markersize=8, color=icolor[i], mec='k', linestyle='dashed')
        plt.errorbar(I_f1, total_LT_nom, total_LT_err,   marker=imarker[i], markersize=8, color=icolor[i], mec='k', linestyle='dashed')
 
        #plt.ylabel('Relative Yield', fontsize=18)
        plt.ylabel('EDTM Live Time', fontsize=18)

        plt.xlabel('Average Current [uA]', fontsize=18)
        plt.xticks(fontsize=14)
        plt.yticks(fontsize=14)
        plt.grid(True)
    
        plt.subplot(1, 2, 2)
        #plot relative T2 scalers for files 1, 2

        #plt.errorbar(  T2_scl_rate_f1 , relY_f1_nom, relY_f1_err,   marker=imarker[i], markersize=8, color=icolor[i], mec='k', linestyle='dashed')
        plt.errorbar(  T2_scl_rate_f1 , total_LT_nom, total_LT_err,   marker=imarker[i], markersize=8, color=icolor[i], mec='k', linestyle='dashed')
     
    
        plt.xlabel('T2 Scaler Rate [kHz]', fontsize=18)
        plt.xticks(fontsize=14)
        plt.yticks(fontsize=14)
        plt.grid(True)
                 
    fig.tight_layout() 
    #plt.legend()
    plt.show()


compare()


#Be9
#relY_f1_err= [5.32194262e-19 1.03384359e-02 7.75697750e-03]
#relY_f2_err= [0.         0.01034461 0.00773343]
#relY_f3_err= [0.         0.00496368 0.01029875 0.01029875 0.00751901 0.00751901]

#B10
#relY_f1_err= [7.63847080e-19 8.00247946e-03]
#relY_f2_err= [0.         0.00799893]
#relY_f3_err= [0.         0.00791032]
