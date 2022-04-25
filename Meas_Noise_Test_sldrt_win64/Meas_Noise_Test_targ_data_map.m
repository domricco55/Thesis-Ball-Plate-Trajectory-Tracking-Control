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
        ;% Auto data (Meas_Noise_Test_P)
        ;%
            section.nData     = 29;
            section.data(29)  = dumData; %prealloc

                    ;% Meas_Noise_Test_P.DiscreteDerivative_ICPrevScaledInput
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% Meas_Noise_Test_P.StreamOutput_MaxMissedTicks
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% Meas_Noise_Test_P.StreamInput_MaxMissedTicks
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% Meas_Noise_Test_P.StreamOutput_YieldWhenWaiting
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% Meas_Noise_Test_P.StreamInput_YieldWhenWaiting
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% Meas_Noise_Test_P.Constant_Value
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% Meas_Noise_Test_P.Gain1_Gain
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 7;

                    ;% Meas_Noise_Test_P.Gain1_Gain_f
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 8;

                    ;% Meas_Noise_Test_P.Gain2_Gain
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 9;

                    ;% Meas_Noise_Test_P.Gain1_Gain_d
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 10;

                    ;% Meas_Noise_Test_P.Gain1_Gain_dd
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 11;

                    ;% Meas_Noise_Test_P.TSamp_WtEt
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 12;

                    ;% Meas_Noise_Test_P.UnitDelay1_InitialCondition
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 13;

                    ;% Meas_Noise_Test_P.Constant_Value_n
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 14;

                    ;% Meas_Noise_Test_P.tau_Gain
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 15;

                    ;% Meas_Noise_Test_P.Constant_Value_j
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 16;

                    ;% Meas_Noise_Test_P.Gain_Gain
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 17;

                    ;% Meas_Noise_Test_P.UnitDelay1_InitialCondition_n
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 18;

                    ;% Meas_Noise_Test_P.tau_Gain_p
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 19;

                    ;% Meas_Noise_Test_P.Constant_Value_i
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 20;

                    ;% Meas_Noise_Test_P.Gain_Gain_b
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 21;

                    ;% Meas_Noise_Test_P.Gain1_Gain_o
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 22;

                    ;% Meas_Noise_Test_P.Gain3_Gain
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 23;

                    ;% Meas_Noise_Test_P.Constant1_Value
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 24;

                    ;% Meas_Noise_Test_P.Gain1_Gain_n
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 25;

                    ;% Meas_Noise_Test_P.UnitDelay2_InitialCondition
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 26;

                    ;% Meas_Noise_Test_P.Constant1_Value_n
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 27;

                    ;% Meas_Noise_Test_P.Gain1_Gain_j
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 28;

                    ;% Meas_Noise_Test_P.UnitDelay2_InitialCondition_n
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 29;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Meas_Noise_Test_P.Gain_Gain_e
                    section.data(1).logicalSrcIdx = 29;
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
        ;% Auto data (Meas_Noise_Test_B)
        ;%
            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Meas_Noise_Test_B.StreamInput_o1
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Meas_Noise_Test_B.StreamInput_o2
                    section.data(1).logicalSrcIdx = 1;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Meas_Noise_Test_B.StreamInput_o3
                    section.data(1).logicalSrcIdx = 2;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(3) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Meas_Noise_Test_B.StreamInput_o4
                    section.data(1).logicalSrcIdx = 3;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(4) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Meas_Noise_Test_B.StreamInput_o5
                    section.data(1).logicalSrcIdx = 4;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(5) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Meas_Noise_Test_B.StreamInput_o6
                    section.data(1).logicalSrcIdx = 5;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(6) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Meas_Noise_Test_B.StreamInput_o7
                    section.data(1).logicalSrcIdx = 6;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(7) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Meas_Noise_Test_B.StreamInput_o8
                    section.data(1).logicalSrcIdx = 7;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(8) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Meas_Noise_Test_B.StreamInput_o9
                    section.data(1).logicalSrcIdx = 8;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(9) = section;
            clear section

            section.nData     = 21;
            section.data(21)  = dumData; %prealloc

                    ;% Meas_Noise_Test_B.bx
                    section.data(1).logicalSrcIdx = 9;
                    section.data(1).dtTransOffset = 0;

                    ;% Meas_Noise_Test_B.IMUx
                    section.data(2).logicalSrcIdx = 10;
                    section.data(2).dtTransOffset = 1;

                    ;% Meas_Noise_Test_B.Gain1
                    section.data(3).logicalSrcIdx = 11;
                    section.data(3).dtTransOffset = 2;

                    ;% Meas_Noise_Test_B.GyroX
                    section.data(4).logicalSrcIdx = 12;
                    section.data(4).dtTransOffset = 3;

                    ;% Meas_Noise_Test_B.Gain1_i
                    section.data(5).logicalSrcIdx = 13;
                    section.data(5).dtTransOffset = 4;

                    ;% Meas_Noise_Test_B.by
                    section.data(6).logicalSrcIdx = 14;
                    section.data(6).dtTransOffset = 5;

                    ;% Meas_Noise_Test_B.IMUy
                    section.data(7).logicalSrcIdx = 15;
                    section.data(7).dtTransOffset = 6;

                    ;% Meas_Noise_Test_B.Gain1_o
                    section.data(8).logicalSrcIdx = 16;
                    section.data(8).dtTransOffset = 7;

                    ;% Meas_Noise_Test_B.GyroY
                    section.data(9).logicalSrcIdx = 17;
                    section.data(9).dtTransOffset = 8;

                    ;% Meas_Noise_Test_B.Gain1_c
                    section.data(10).logicalSrcIdx = 18;
                    section.data(10).dtTransOffset = 9;

                    ;% Meas_Noise_Test_B.MeasuredOutput
                    section.data(11).logicalSrcIdx = 19;
                    section.data(11).dtTransOffset = 10;

                    ;% Meas_Noise_Test_B.TSamp
                    section.data(12).logicalSrcIdx = 20;
                    section.data(12).dtTransOffset = 16;

                    ;% Meas_Noise_Test_B.Diff
                    section.data(13).logicalSrcIdx = 21;
                    section.data(13).dtTransOffset = 17;

                    ;% Meas_Noise_Test_B.Product1
                    section.data(14).logicalSrcIdx = 22;
                    section.data(14).dtTransOffset = 18;

                    ;% Meas_Noise_Test_B.bx_dot
                    section.data(15).logicalSrcIdx = 23;
                    section.data(15).dtTransOffset = 19;

                    ;% Meas_Noise_Test_B.by_dot
                    section.data(16).logicalSrcIdx = 24;
                    section.data(16).dtTransOffset = 20;

                    ;% Meas_Noise_Test_B.TimingParity
                    section.data(17).logicalSrcIdx = 25;
                    section.data(17).dtTransOffset = 21;

                    ;% Meas_Noise_Test_B.Sum1
                    section.data(18).logicalSrcIdx = 26;
                    section.data(18).dtTransOffset = 22;

                    ;% Meas_Noise_Test_B.Sum3
                    section.data(19).logicalSrcIdx = 27;
                    section.data(19).dtTransOffset = 23;

                    ;% Meas_Noise_Test_B.Sum1_m
                    section.data(20).logicalSrcIdx = 28;
                    section.data(20).dtTransOffset = 24;

                    ;% Meas_Noise_Test_B.Sum3_j
                    section.data(21).logicalSrcIdx = 29;
                    section.data(21).dtTransOffset = 25;

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
        nTotSects     = 2;
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
        ;% Auto data (Meas_Noise_Test_DW)
        ;%
            section.nData     = 5;
            section.data(5)  = dumData; %prealloc

                    ;% Meas_Noise_Test_DW.UD_DSTATE
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% Meas_Noise_Test_DW.UnitDelay1_DSTATE
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% Meas_Noise_Test_DW.UnitDelay1_DSTATE_l
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% Meas_Noise_Test_DW.UnitDelay2_DSTATE
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% Meas_Noise_Test_DW.UnitDelay2_DSTATE_p
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 14;
            section.data(14)  = dumData; %prealloc

                    ;% Meas_Noise_Test_DW.StreamOutput_PWORK
                    section.data(1).logicalSrcIdx = 5;
                    section.data(1).dtTransOffset = 0;

                    ;% Meas_Noise_Test_DW.StreamInput_PWORK
                    section.data(2).logicalSrcIdx = 6;
                    section.data(2).dtTransOffset = 2;

                    ;% Meas_Noise_Test_DW.xactual1_PWORK.LoggedData
                    section.data(3).logicalSrcIdx = 7;
                    section.data(3).dtTransOffset = 4;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_DiscreteDerivative_at_outport_0_PWORK.AQHandles
                    section.data(4).logicalSrcIdx = 8;
                    section.data(4).dtTransOffset = 5;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_DiscreteVaryingLowpass_at_outport_0_PWORK.AQHandles
                    section.data(5).logicalSrcIdx = 9;
                    section.data(5).dtTransOffset = 6;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_Gain1_at_outport_0_PWORK.AQHandles
                    section.data(6).logicalSrcIdx = 10;
                    section.data(6).dtTransOffset = 7;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_Gain2_at_outport_0_PWORK.AQHandles
                    section.data(7).logicalSrcIdx = 11;
                    section.data(7).dtTransOffset = 8;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_Gain3_at_outport_0_PWORK.AQHandles
                    section.data(8).logicalSrcIdx = 12;
                    section.data(8).dtTransOffset = 9;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_Gain_at_outport_0_PWORK.AQHandles
                    section.data(9).logicalSrcIdx = 13;
                    section.data(9).dtTransOffset = 10;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_StringtoDouble4_at_outport_0_PWORK.AQHandles
                    section.data(10).logicalSrcIdx = 14;
                    section.data(10).dtTransOffset = 11;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_StringtoDouble5_at_outport_0_PWORK.AQHandles
                    section.data(11).logicalSrcIdx = 15;
                    section.data(11).dtTransOffset = 12;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_StringtoDouble6_at_outport_0_PWORK.AQHandles
                    section.data(12).logicalSrcIdx = 16;
                    section.data(12).dtTransOffset = 13;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_StringtoDouble7_at_outport_0_PWORK.AQHandles
                    section.data(13).logicalSrcIdx = 17;
                    section.data(13).dtTransOffset = 14;

                    ;% Meas_Noise_Test_DW.TAQSigLogging_InsertedFor_StringtoDouble8_at_outport_0_PWORK.AQHandles
                    section.data(14).logicalSrcIdx = 18;
                    section.data(14).dtTransOffset = 15;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
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


    targMap.checksum0 = 1600017397;
    targMap.checksum1 = 1475453995;
    targMap.checksum2 = 2992063876;
    targMap.checksum3 = 594787750;

