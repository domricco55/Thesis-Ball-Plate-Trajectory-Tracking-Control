    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 2;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc paramMap
        ;%
        paramMap.nSections           = nTotSects;
        paramMap.sectIdxOffset       = sectIdxOffset;
            paramMap.sections(nTotSects) = dumSection; %prealloc
        paramMap.nTotData            = -1;

        ;%
        ;% Auto data (FSFB_FF_HIL_quick_dirty_P)
        ;%
            section.nData     = 49;
            section.data(49)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_P.A
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% FSFB_FF_HIL_quick_dirty_P.B
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 64;

                    ;% FSFB_FF_HIL_quick_dirty_P.H
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 80;

                    ;% FSFB_FF_HIL_quick_dirty_P.K1
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 128;

                    ;% FSFB_FF_HIL_quick_dirty_P.K2
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 133;

                    ;% FSFB_FF_HIL_quick_dirty_P.Q_KF
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 138;

                    ;% FSFB_FF_HIL_quick_dirty_P.R_KF
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 202;

                    ;% FSFB_FF_HIL_quick_dirty_P.Tau
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 238;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteDerivative_ICPrevScaledInput
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 239;

                    ;% FSFB_FF_HIL_quick_dirty_P.StreamInput_MaxMissedTicks
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 240;

                    ;% FSFB_FF_HIL_quick_dirty_P.StreamOutput_MaxMissedTicks
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 241;

                    ;% FSFB_FF_HIL_quick_dirty_P.StreamInput_YieldWhenWaiting
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 242;

                    ;% FSFB_FF_HIL_quick_dirty_P.StreamOutput_YieldWhenWaiting
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 243;

                    ;% FSFB_FF_HIL_quick_dirty_P._Y0
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 244;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 252;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_g
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 253;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_n
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 254;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain2_Gain
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 255;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain3_Gain
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 256;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_b
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 257;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_k
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 258;

                    ;% FSFB_FF_HIL_quick_dirty_P.Step_Time
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 259;

                    ;% FSFB_FF_HIL_quick_dirty_P.Step_Y0
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 260;

                    ;% FSFB_FF_HIL_quick_dirty_P.Step_YFinal
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 261;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_gainval
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 262;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_IC
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 263;

                    ;% FSFB_FF_HIL_quick_dirty_P.UnitDelay1_InitialCondition
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 264;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_gainval_p
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 272;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_IC_l
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 273;

                    ;% FSFB_FF_HIL_quick_dirty_P.GearRatioAssumption_Gain
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 274;

                    ;% FSFB_FF_HIL_quick_dirty_P.Saturation1_UpperSat
                    section.data(31).logicalSrcIdx = 30;
                    section.data(31).dtTransOffset = 275;

                    ;% FSFB_FF_HIL_quick_dirty_P.Saturation1_LowerSat
                    section.data(32).logicalSrcIdx = 31;
                    section.data(32).dtTransOffset = 276;

                    ;% FSFB_FF_HIL_quick_dirty_P.UnitDelay_InitialCondition
                    section.data(33).logicalSrcIdx = 32;
                    section.data(33).dtTransOffset = 277;

                    ;% FSFB_FF_HIL_quick_dirty_P.TSamp_WtEt
                    section.data(34).logicalSrcIdx = 33;
                    section.data(34).dtTransOffset = 341;

                    ;% FSFB_FF_HIL_quick_dirty_P.UnitDelay1_InitialCondition_g
                    section.data(35).logicalSrcIdx = 34;
                    section.data(35).dtTransOffset = 342;

                    ;% FSFB_FF_HIL_quick_dirty_P.Constant_Value
                    section.data(36).logicalSrcIdx = 35;
                    section.data(36).dtTransOffset = 343;

                    ;% FSFB_FF_HIL_quick_dirty_P.tau_Gain
                    section.data(37).logicalSrcIdx = 36;
                    section.data(37).dtTransOffset = 344;

                    ;% FSFB_FF_HIL_quick_dirty_P.Constant_Value_a
                    section.data(38).logicalSrcIdx = 37;
                    section.data(38).dtTransOffset = 345;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain_Gain
                    section.data(39).logicalSrcIdx = 38;
                    section.data(39).dtTransOffset = 346;

                    ;% FSFB_FF_HIL_quick_dirty_P.UnitDelay1_InitialCondition_l
                    section.data(40).logicalSrcIdx = 39;
                    section.data(40).dtTransOffset = 347;

                    ;% FSFB_FF_HIL_quick_dirty_P.tau_Gain_h
                    section.data(41).logicalSrcIdx = 40;
                    section.data(41).dtTransOffset = 348;

                    ;% FSFB_FF_HIL_quick_dirty_P.Constant_Value_f
                    section.data(42).logicalSrcIdx = 41;
                    section.data(42).dtTransOffset = 349;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain_Gain_g
                    section.data(43).logicalSrcIdx = 42;
                    section.data(43).dtTransOffset = 350;

                    ;% FSFB_FF_HIL_quick_dirty_P.Constant1_Value
                    section.data(44).logicalSrcIdx = 43;
                    section.data(44).dtTransOffset = 351;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_bv
                    section.data(45).logicalSrcIdx = 44;
                    section.data(45).dtTransOffset = 352;

                    ;% FSFB_FF_HIL_quick_dirty_P.UnitDelay2_InitialCondition
                    section.data(46).logicalSrcIdx = 45;
                    section.data(46).dtTransOffset = 353;

                    ;% FSFB_FF_HIL_quick_dirty_P.Constant1_Value_d
                    section.data(47).logicalSrcIdx = 46;
                    section.data(47).dtTransOffset = 354;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_f
                    section.data(48).logicalSrcIdx = 47;
                    section.data(48).dtTransOffset = 355;

                    ;% FSFB_FF_HIL_quick_dirty_P.UnitDelay2_InitialCondition_p
                    section.data(49).logicalSrcIdx = 48;
                    section.data(49).dtTransOffset = 356;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain_Gain_a
                    section.data(1).logicalSrcIdx = 49;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section


            ;%
            ;% Non-auto Data (parameter)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        paramMap.nTotData = nTotData;



    ;%**************************
    ;% Create Block Output Map *
    ;%**************************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 10;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc sigMap
        ;%
        sigMap.nSections           = nTotSects;
        sigMap.sectIdxOffset       = sectIdxOffset;
            sigMap.sections(nTotSects) = dumSection; %prealloc
        sigMap.nTotData            = -1;

        ;%
        ;% Auto data (FSFB_FF_HIL_quick_dirty_B)
        ;%
            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_B.StreamInput_o1
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_B.StreamInput_o2
                    section.data(1).logicalSrcIdx = 1;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_B.StreamInput_o3
                    section.data(1).logicalSrcIdx = 2;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(3) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_B.StreamInput_o4
                    section.data(1).logicalSrcIdx = 3;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(4) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_B.StreamInput_o5
                    section.data(1).logicalSrcIdx = 4;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(5) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_B.StreamInput_o6
                    section.data(1).logicalSrcIdx = 5;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(6) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_B.StreamInput_o7
                    section.data(1).logicalSrcIdx = 6;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(7) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_B.StreamInput_o8
                    section.data(1).logicalSrcIdx = 7;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(8) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_B.StreamInput_o9
                    section.data(1).logicalSrcIdx = 8;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(9) = section;
            clear section

            section.nData     = 37;
            section.data(37)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_B.bx
                    section.data(1).logicalSrcIdx = 9;
                    section.data(1).dtTransOffset = 0;

                    ;% FSFB_FF_HIL_quick_dirty_B.bx_dot
                    section.data(2).logicalSrcIdx = 10;
                    section.data(2).dtTransOffset = 1;

                    ;% FSFB_FF_HIL_quick_dirty_B.IMUx
                    section.data(3).logicalSrcIdx = 11;
                    section.data(3).dtTransOffset = 2;

                    ;% FSFB_FF_HIL_quick_dirty_B.Gain1
                    section.data(4).logicalSrcIdx = 12;
                    section.data(4).dtTransOffset = 3;

                    ;% FSFB_FF_HIL_quick_dirty_B.GyroX
                    section.data(5).logicalSrcIdx = 13;
                    section.data(5).dtTransOffset = 4;

                    ;% FSFB_FF_HIL_quick_dirty_B.Gain1_k
                    section.data(6).logicalSrcIdx = 14;
                    section.data(6).dtTransOffset = 5;

                    ;% FSFB_FF_HIL_quick_dirty_B.by
                    section.data(7).logicalSrcIdx = 15;
                    section.data(7).dtTransOffset = 6;

                    ;% FSFB_FF_HIL_quick_dirty_B.by_dot
                    section.data(8).logicalSrcIdx = 16;
                    section.data(8).dtTransOffset = 7;

                    ;% FSFB_FF_HIL_quick_dirty_B.IMUy
                    section.data(9).logicalSrcIdx = 17;
                    section.data(9).dtTransOffset = 8;

                    ;% FSFB_FF_HIL_quick_dirty_B.Gain1_l
                    section.data(10).logicalSrcIdx = 18;
                    section.data(10).dtTransOffset = 9;

                    ;% FSFB_FF_HIL_quick_dirty_B.GyroY
                    section.data(11).logicalSrcIdx = 19;
                    section.data(11).dtTransOffset = 10;

                    ;% FSFB_FF_HIL_quick_dirty_B.Gain1_n
                    section.data(12).logicalSrcIdx = 20;
                    section.data(12).dtTransOffset = 11;

                    ;% FSFB_FF_HIL_quick_dirty_B.Step
                    section.data(13).logicalSrcIdx = 21;
                    section.data(13).dtTransOffset = 12;

                    ;% FSFB_FF_HIL_quick_dirty_B.xmeasured
                    section.data(14).logicalSrcIdx = 22;
                    section.data(14).dtTransOffset = 13;

                    ;% FSFB_FF_HIL_quick_dirty_B.integratederror
                    section.data(15).logicalSrcIdx = 23;
                    section.data(15).dtTransOffset = 21;

                    ;% FSFB_FF_HIL_quick_dirty_B.x_filtered
                    section.data(16).logicalSrcIdx = 24;
                    section.data(16).dtTransOffset = 22;

                    ;% FSFB_FF_HIL_quick_dirty_B.e_vec
                    section.data(17).logicalSrcIdx = 25;
                    section.data(17).dtTransOffset = 30;

                    ;% FSFB_FF_HIL_quick_dirty_B.integratederror_d
                    section.data(18).logicalSrcIdx = 26;
                    section.data(18).dtTransOffset = 34;

                    ;% FSFB_FF_HIL_quick_dirty_B.ey_vec
                    section.data(19).logicalSrcIdx = 27;
                    section.data(19).dtTransOffset = 35;

                    ;% FSFB_FF_HIL_quick_dirty_B.u_des
                    section.data(20).logicalSrcIdx = 28;
                    section.data(20).dtTransOffset = 39;

                    ;% FSFB_FF_HIL_quick_dirty_B.Torque_Sat
                    section.data(21).logicalSrcIdx = 29;
                    section.data(21).dtTransOffset = 41;

                    ;% FSFB_FF_HIL_quick_dirty_B.Gain5
                    section.data(22).logicalSrcIdx = 30;
                    section.data(22).dtTransOffset = 43;

                    ;% FSFB_FF_HIL_quick_dirty_B.UnitDelay
                    section.data(23).logicalSrcIdx = 31;
                    section.data(23).dtTransOffset = 51;

                    ;% FSFB_FF_HIL_quick_dirty_B.aposteriori
                    section.data(24).logicalSrcIdx = 32;
                    section.data(24).dtTransOffset = 115;

                    ;% FSFB_FF_HIL_quick_dirty_B.TSamp
                    section.data(25).logicalSrcIdx = 33;
                    section.data(25).dtTransOffset = 123;

                    ;% FSFB_FF_HIL_quick_dirty_B.Diff
                    section.data(26).logicalSrcIdx = 34;
                    section.data(26).dtTransOffset = 124;

                    ;% FSFB_FF_HIL_quick_dirty_B.Product1
                    section.data(27).logicalSrcIdx = 35;
                    section.data(27).dtTransOffset = 125;

                    ;% FSFB_FF_HIL_quick_dirty_B.TimingParity
                    section.data(28).logicalSrcIdx = 36;
                    section.data(28).dtTransOffset = 126;

                    ;% FSFB_FF_HIL_quick_dirty_B.Sum1
                    section.data(29).logicalSrcIdx = 37;
                    section.data(29).dtTransOffset = 127;

                    ;% FSFB_FF_HIL_quick_dirty_B.Sum3
                    section.data(30).logicalSrcIdx = 38;
                    section.data(30).dtTransOffset = 128;

                    ;% FSFB_FF_HIL_quick_dirty_B.Sum1_b
                    section.data(31).logicalSrcIdx = 39;
                    section.data(31).dtTransOffset = 129;

                    ;% FSFB_FF_HIL_quick_dirty_B.Sum3_b
                    section.data(32).logicalSrcIdx = 40;
                    section.data(32).dtTransOffset = 130;

                    ;% FSFB_FF_HIL_quick_dirty_B.out1
                    section.data(33).logicalSrcIdx = 41;
                    section.data(33).dtTransOffset = 131;

                    ;% FSFB_FF_HIL_quick_dirty_B.P_k
                    section.data(34).logicalSrcIdx = 42;
                    section.data(34).dtTransOffset = 133;

                    ;% FSFB_FF_HIL_quick_dirty_B.smoothed_y
                    section.data(35).logicalSrcIdx = 43;
                    section.data(35).dtTransOffset = 197;

                    ;% FSFB_FF_HIL_quick_dirty_B.smoothed_x
                    section.data(36).logicalSrcIdx = 44;
                    section.data(36).dtTransOffset = 201;

                    ;% FSFB_FF_HIL_quick_dirty_B.In
                    section.data(37).logicalSrcIdx = 45;
                    section.data(37).dtTransOffset = 205;

            nTotData = nTotData + section.nData;
            sigMap.sections(10) = section;
            clear section


            ;%
            ;% Non-auto Data (signal)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        sigMap.nTotData = nTotData;



    ;%*******************
    ;% Create DWork Map *
    ;%*******************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 3;
        sectIdxOffset = 10;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc dworkMap
        ;%
        dworkMap.nSections           = nTotSects;
        dworkMap.sectIdxOffset       = sectIdxOffset;
            dworkMap.sections(nTotSects) = dumSection; %prealloc
        dworkMap.nTotData            = -1;

        ;%
        ;% Auto data (FSFB_FF_HIL_quick_dirty_DW)
        ;%
            section.nData     = 9;
            section.data(9)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_b
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 9;

                    ;% FSFB_FF_HIL_quick_dirty_DW.UnitDelay_DSTATE
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 10;

                    ;% FSFB_FF_HIL_quick_dirty_DW.UD_DSTATE
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 74;

                    ;% FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE_n
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 75;

                    ;% FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE_j
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 76;

                    ;% FSFB_FF_HIL_quick_dirty_DW.UnitDelay2_DSTATE
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 77;

                    ;% FSFB_FF_HIL_quick_dirty_DW.UnitDelay2_DSTATE_h
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 78;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 32;
            section.data(32)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope_PWORK.LoggedData
                    section.data(1).logicalSrcIdx = 9;
                    section.data(1).dtTransOffset = 0;

                    ;% FSFB_FF_HIL_quick_dirty_DW.StreamInput_PWORK
                    section.data(2).logicalSrcIdx = 10;
                    section.data(2).dtTransOffset = 1;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope1_PWORK.LoggedData
                    section.data(3).logicalSrcIdx = 11;
                    section.data(3).dtTransOffset = 3;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope2_PWORK.LoggedData
                    section.data(4).logicalSrcIdx = 12;
                    section.data(4).dtTransOffset = 4;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope3_PWORK.LoggedData
                    section.data(5).logicalSrcIdx = 13;
                    section.data(5).dtTransOffset = 5;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope4_PWORK.LoggedData
                    section.data(6).logicalSrcIdx = 14;
                    section.data(6).dtTransOffset = 6;

                    ;% FSFB_FF_HIL_quick_dirty_DW.controlleroutput_PWORK.LoggedData
                    section.data(7).logicalSrcIdx = 15;
                    section.data(7).dtTransOffset = 7;

                    ;% FSFB_FF_HIL_quick_dirty_DW.xmeasured_PWORK.LoggedData
                    section.data(8).logicalSrcIdx = 16;
                    section.data(8).dtTransOffset = 8;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope_PWORK_j.LoggedData
                    section.data(9).logicalSrcIdx = 17;
                    section.data(9).dtTransOffset = 9;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope1_PWORK_a.LoggedData
                    section.data(10).logicalSrcIdx = 18;
                    section.data(10).dtTransOffset = 10;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope_PWORK_d.LoggedData
                    section.data(11).logicalSrcIdx = 19;
                    section.data(11).dtTransOffset = 11;

                    ;% FSFB_FF_HIL_quick_dirty_DW.ToWorkspace_PWORK.LoggedData
                    section.data(12).logicalSrcIdx = 20;
                    section.data(12).dtTransOffset = 13;

                    ;% FSFB_FF_HIL_quick_dirty_DW.ToWorkspace2_PWORK.LoggedData
                    section.data(13).logicalSrcIdx = 21;
                    section.data(13).dtTransOffset = 14;

                    ;% FSFB_FF_HIL_quick_dirty_DW.beta_s_PWORK.LoggedData
                    section.data(14).logicalSrcIdx = 22;
                    section.data(14).dtTransOffset = 15;

                    ;% FSFB_FF_HIL_quick_dirty_DW.gamma_s_PWORK.LoggedData
                    section.data(15).logicalSrcIdx = 23;
                    section.data(15).dtTransOffset = 16;

                    ;% FSFB_FF_HIL_quick_dirty_DW.x_s_PWORK.LoggedData
                    section.data(16).logicalSrcIdx = 24;
                    section.data(16).dtTransOffset = 17;

                    ;% FSFB_FF_HIL_quick_dirty_DW.y_s_PWORK.LoggedData
                    section.data(17).logicalSrcIdx = 25;
                    section.data(17).dtTransOffset = 18;

                    ;% FSFB_FF_HIL_quick_dirty_DW.StreamOutput_PWORK
                    section.data(18).logicalSrcIdx = 26;
                    section.data(18).dtTransOffset = 19;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_KalmanFilter_at_outport_0_PWORK.AQHandles
                    section.data(19).logicalSrcIdx = 27;
                    section.data(19).dtTransOffset = 21;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_Saturation1_at_outport_0_PWORK.AQHandles
                    section.data(20).logicalSrcIdx = 28;
                    section.data(20).dtTransOffset = 22;

                    ;% FSFB_FF_HIL_quick_dirty_DW.ToWorkspace1_PWORK.LoggedData
                    section.data(21).logicalSrcIdx = 29;
                    section.data(21).dtTransOffset = 23;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_DiscreteDerivative_at_outport_0_PWORK.AQHandles
                    section.data(22).logicalSrcIdx = 30;
                    section.data(22).dtTransOffset = 24;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_DiscreteVaryingLowpass_at_outport_0_PWORK.AQHandles
                    section.data(23).logicalSrcIdx = 31;
                    section.data(23).dtTransOffset = 25;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_Gain1_at_outport_0_PWORK.AQHandles
                    section.data(24).logicalSrcIdx = 32;
                    section.data(24).dtTransOffset = 26;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_Gain2_at_outport_0_PWORK.AQHandles
                    section.data(25).logicalSrcIdx = 33;
                    section.data(25).dtTransOffset = 27;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_Gain3_at_outport_0_PWORK.AQHandles
                    section.data(26).logicalSrcIdx = 34;
                    section.data(26).dtTransOffset = 28;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_Gain_at_outport_0_PWORK.AQHandles
                    section.data(27).logicalSrcIdx = 35;
                    section.data(27).dtTransOffset = 29;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_StringtoDouble4_at_outport_0_PWORK.AQHandles
                    section.data(28).logicalSrcIdx = 36;
                    section.data(28).dtTransOffset = 30;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_StringtoDouble5_at_outport_0_PWORK.AQHandles
                    section.data(29).logicalSrcIdx = 37;
                    section.data(29).dtTransOffset = 31;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_StringtoDouble6_at_outport_0_PWORK.AQHandles
                    section.data(30).logicalSrcIdx = 38;
                    section.data(30).dtTransOffset = 32;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_StringtoDouble7_at_outport_0_PWORK.AQHandles
                    section.data(31).logicalSrcIdx = 39;
                    section.data(31).dtTransOffset = 33;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_StringtoDouble8_at_outport_0_PWORK.AQHandles
                    section.data(32).logicalSrcIdx = 40;
                    section.data(32).dtTransOffset = 34;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_DW.SampleandHold_SubsysRanBC
                    section.data(1).logicalSrcIdx = 41;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section


            ;%
            ;% Non-auto Data (dwork)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        dworkMap.nTotData = nTotData;



    ;%
    ;% Add individual maps to base struct.
    ;%

    targMap.paramMap  = paramMap;
    targMap.signalMap = sigMap;
    targMap.dworkMap  = dworkMap;

    ;%
    ;% Add checksums to base struct.
    ;%


    targMap.checksum0 = 572516581;
    targMap.checksum1 = 3075342302;
    targMap.checksum2 = 3550202672;
    targMap.checksum3 = 2433281044;

