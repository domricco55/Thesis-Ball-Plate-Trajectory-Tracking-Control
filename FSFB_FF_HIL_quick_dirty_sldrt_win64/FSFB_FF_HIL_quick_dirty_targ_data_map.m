    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 3;
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
            section.nData     = 31;
            section.data(31)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_P.K1
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% FSFB_FF_HIL_quick_dirty_P.K2
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 5;

                    ;% FSFB_FF_HIL_quick_dirty_P.Tau
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 10;

                    ;% FSFB_FF_HIL_quick_dirty_P.Ts
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 11;

                    ;% FSFB_FF_HIL_quick_dirty_P.StreamInput_MaxMissedTicks
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 12;

                    ;% FSFB_FF_HIL_quick_dirty_P.StreamOutput_MaxMissedTicks
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 13;

                    ;% FSFB_FF_HIL_quick_dirty_P.StreamInput_YieldWhenWaiting
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 14;

                    ;% FSFB_FF_HIL_quick_dirty_P.StreamOutput_YieldWhenWaiting
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 15;

                    ;% FSFB_FF_HIL_quick_dirty_P._Y0
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 16;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 24;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_g
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 25;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_n
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 26;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain2_Gain
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 27;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain3_Gain
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 28;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_b
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 29;

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_k
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 30;

                    ;% FSFB_FF_HIL_quick_dirty_P.Step_Y0
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 31;

                    ;% FSFB_FF_HIL_quick_dirty_P.Step_YFinal
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 32;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_gainval
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 33;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_IC
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 34;

                    ;% FSFB_FF_HIL_quick_dirty_P.Constant_Value
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 35;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_gainval_p
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 36;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_IC_l
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 37;

                    ;% FSFB_FF_HIL_quick_dirty_P.Step1_Y0
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 38;

                    ;% FSFB_FF_HIL_quick_dirty_P.Step1_YFinal
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 39;

                    ;% FSFB_FF_HIL_quick_dirty_P.Constant_Value_h
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 40;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_gainval_c
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 42;

                    ;% FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_IC_h
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 43;

                    ;% FSFB_FF_HIL_quick_dirty_P.GearRatioAssumption_Gain
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 44;

                    ;% FSFB_FF_HIL_quick_dirty_P.Saturation1_UpperSat
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 45;

                    ;% FSFB_FF_HIL_quick_dirty_P.Saturation1_LowerSat
                    section.data(31).logicalSrcIdx = 30;
                    section.data(31).dtTransOffset = 46;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_P.Gain_Gain
                    section.data(1).logicalSrcIdx = 31;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_P.ManualSwitch_CurrentSetting
                    section.data(1).logicalSrcIdx = 32;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(3) = section;
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

            section.nData     = 26;
            section.data(26)  = dumData; %prealloc

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

                    ;% FSFB_FF_HIL_quick_dirty_B.integratederror
                    section.data(14).logicalSrcIdx = 22;
                    section.data(14).dtTransOffset = 13;

                    ;% FSFB_FF_HIL_quick_dirty_B.e_vec
                    section.data(15).logicalSrcIdx = 23;
                    section.data(15).dtTransOffset = 14;

                    ;% FSFB_FF_HIL_quick_dirty_B.integratederror_d
                    section.data(16).logicalSrcIdx = 24;
                    section.data(16).dtTransOffset = 18;

                    ;% FSFB_FF_HIL_quick_dirty_B.ey_vec
                    section.data(17).logicalSrcIdx = 25;
                    section.data(17).dtTransOffset = 19;

                    ;% FSFB_FF_HIL_quick_dirty_B.Product
                    section.data(18).logicalSrcIdx = 26;
                    section.data(18).dtTransOffset = 23;

                    ;% FSFB_FF_HIL_quick_dirty_B.ManualSwitch
                    section.data(19).logicalSrcIdx = 27;
                    section.data(19).dtTransOffset = 25;

                    ;% FSFB_FF_HIL_quick_dirty_B.xb_int
                    section.data(20).logicalSrcIdx = 28;
                    section.data(20).dtTransOffset = 27;

                    ;% FSFB_FF_HIL_quick_dirty_B.TimingParity
                    section.data(21).logicalSrcIdx = 29;
                    section.data(21).dtTransOffset = 28;

                    ;% FSFB_FF_HIL_quick_dirty_B.Torque_Sat
                    section.data(22).logicalSrcIdx = 30;
                    section.data(22).dtTransOffset = 29;

                    ;% FSFB_FF_HIL_quick_dirty_B.out1
                    section.data(23).logicalSrcIdx = 31;
                    section.data(23).dtTransOffset = 31;

                    ;% FSFB_FF_HIL_quick_dirty_B.smoothed_y
                    section.data(24).logicalSrcIdx = 32;
                    section.data(24).dtTransOffset = 33;

                    ;% FSFB_FF_HIL_quick_dirty_B.smoothed_x
                    section.data(25).logicalSrcIdx = 33;
                    section.data(25).dtTransOffset = 37;

                    ;% FSFB_FF_HIL_quick_dirty_B.In
                    section.data(26).logicalSrcIdx = 34;
                    section.data(26).dtTransOffset = 41;

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
            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_b
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_g
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 26;
            section.data(26)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope_PWORK.LoggedData
                    section.data(1).logicalSrcIdx = 3;
                    section.data(1).dtTransOffset = 0;

                    ;% FSFB_FF_HIL_quick_dirty_DW.StreamInput_PWORK
                    section.data(2).logicalSrcIdx = 4;
                    section.data(2).dtTransOffset = 1;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope1_PWORK.LoggedData
                    section.data(3).logicalSrcIdx = 5;
                    section.data(3).dtTransOffset = 3;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope3_PWORK.LoggedData
                    section.data(4).logicalSrcIdx = 6;
                    section.data(4).dtTransOffset = 4;

                    ;% FSFB_FF_HIL_quick_dirty_DW.controlleroutput_PWORK.LoggedData
                    section.data(5).logicalSrcIdx = 7;
                    section.data(5).dtTransOffset = 5;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope_PWORK_j.LoggedData
                    section.data(6).logicalSrcIdx = 8;
                    section.data(6).dtTransOffset = 6;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope_PWORK_d.LoggedData
                    section.data(7).logicalSrcIdx = 9;
                    section.data(7).dtTransOffset = 7;

                    ;% FSFB_FF_HIL_quick_dirty_DW.ToWorkspace_PWORK.LoggedData
                    section.data(8).logicalSrcIdx = 10;
                    section.data(8).dtTransOffset = 9;

                    ;% FSFB_FF_HIL_quick_dirty_DW.ToWorkspace2_PWORK.LoggedData
                    section.data(9).logicalSrcIdx = 11;
                    section.data(9).dtTransOffset = 10;

                    ;% FSFB_FF_HIL_quick_dirty_DW.beta_s_PWORK.LoggedData
                    section.data(10).logicalSrcIdx = 12;
                    section.data(10).dtTransOffset = 11;

                    ;% FSFB_FF_HIL_quick_dirty_DW.gamma_s_PWORK.LoggedData
                    section.data(11).logicalSrcIdx = 13;
                    section.data(11).dtTransOffset = 12;

                    ;% FSFB_FF_HIL_quick_dirty_DW.x_s_PWORK.LoggedData
                    section.data(12).logicalSrcIdx = 14;
                    section.data(12).dtTransOffset = 13;

                    ;% FSFB_FF_HIL_quick_dirty_DW.y_s_PWORK.LoggedData
                    section.data(13).logicalSrcIdx = 15;
                    section.data(13).dtTransOffset = 14;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_DiscreteTimeIntegrator_at_outport_0_PWORK.AQHandles
                    section.data(14).logicalSrcIdx = 16;
                    section.data(14).dtTransOffset = 15;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_Gain1_at_outport_0_PWORK.AQHandles
                    section.data(15).logicalSrcIdx = 17;
                    section.data(15).dtTransOffset = 16;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_Gain2_at_outport_0_PWORK.AQHandles
                    section.data(16).logicalSrcIdx = 18;
                    section.data(16).dtTransOffset = 17;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_Gain3_at_outport_0_PWORK.AQHandles
                    section.data(17).logicalSrcIdx = 19;
                    section.data(17).dtTransOffset = 18;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_Gain_at_outport_0_PWORK.AQHandles
                    section.data(18).logicalSrcIdx = 20;
                    section.data(18).dtTransOffset = 19;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_StringtoDouble4_at_outport_0_PWORK.AQHandles
                    section.data(19).logicalSrcIdx = 21;
                    section.data(19).dtTransOffset = 20;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_StringtoDouble5_at_outport_0_PWORK.AQHandles
                    section.data(20).logicalSrcIdx = 22;
                    section.data(20).dtTransOffset = 21;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_StringtoDouble6_at_outport_0_PWORK.AQHandles
                    section.data(21).logicalSrcIdx = 23;
                    section.data(21).dtTransOffset = 22;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_StringtoDouble7_at_outport_0_PWORK.AQHandles
                    section.data(22).logicalSrcIdx = 24;
                    section.data(22).dtTransOffset = 23;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_StringtoDouble8_at_outport_0_PWORK.AQHandles
                    section.data(23).logicalSrcIdx = 25;
                    section.data(23).dtTransOffset = 24;

                    ;% FSFB_FF_HIL_quick_dirty_DW.Scope_PWORK_n.LoggedData
                    section.data(24).logicalSrcIdx = 26;
                    section.data(24).dtTransOffset = 25;

                    ;% FSFB_FF_HIL_quick_dirty_DW.StreamOutput_PWORK
                    section.data(25).logicalSrcIdx = 27;
                    section.data(25).dtTransOffset = 26;

                    ;% FSFB_FF_HIL_quick_dirty_DW.TAQSigLogging_InsertedFor_Saturation1_at_outport_0_PWORK.AQHandles
                    section.data(26).logicalSrcIdx = 28;
                    section.data(26).dtTransOffset = 28;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% FSFB_FF_HIL_quick_dirty_DW.SampleandHold_SubsysRanBC
                    section.data(1).logicalSrcIdx = 29;
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


    targMap.checksum0 = 2957840969;
    targMap.checksum1 = 608291789;
    targMap.checksum2 = 1731593454;
    targMap.checksum3 = 91589513;

