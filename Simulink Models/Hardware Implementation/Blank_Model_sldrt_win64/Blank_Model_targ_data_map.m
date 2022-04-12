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
        ;% Auto data (Blank_Model_P)
        ;%
            section.nData     = 31;
            section.data(31)  = dumData; %prealloc

                    ;% Blank_Model_P.DiscreteDerivative1_ICPrevScaledInput
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% Blank_Model_P.DiscreteDerivative_ICPrevScaledInput
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% Blank_Model_P.StreamInput_MaxMissedTicks
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% Blank_Model_P.StreamOutput_MaxMissedTicks
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% Blank_Model_P.StreamInput_YieldWhenWaiting
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% Blank_Model_P.StreamOutput_YieldWhenWaiting
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% Blank_Model_P.Gain1_Gain
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% Blank_Model_P.Gain1_Gain_i
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% Blank_Model_P.Gain1_Gain_j
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

                    ;% Blank_Model_P.Gain1_Gain_iv
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 9;

                    ;% Blank_Model_P.Gain1_Gain_ip
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 10;

                    ;% Blank_Model_P.Gain2_Gain
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 11;

                    ;% Blank_Model_P.Gain3_Gain
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 12;

                    ;% Blank_Model_P.Gain_Gain
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 13;

                    ;% Blank_Model_P.Gain_Gain_f
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 14;

                    ;% Blank_Model_P.TSamp_WtEt
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 15;

                    ;% Blank_Model_P.TSamp_WtEt_f
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 16;

                    ;% Blank_Model_P.Gain_Gain_j
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 17;

                    ;% Blank_Model_P.Gain_Gain_n
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 18;

                    ;% Blank_Model_P.DiscreteTimeIntegrator_gainval
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 19;

                    ;% Blank_Model_P.DiscreteTimeIntegrator_IC
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 20;

                    ;% Blank_Model_P.Gain_Gain_jf
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 21;

                    ;% Blank_Model_P.DiscreteTimeIntegrator1_gainval
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 22;

                    ;% Blank_Model_P.DiscreteTimeIntegrator1_IC
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 23;

                    ;% Blank_Model_P.Gain_Gain_g
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 24;

                    ;% Blank_Model_P.Constant_Value
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 25;

                    ;% Blank_Model_P.Constant1_Value
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 26;

                    ;% Blank_Model_P.GearRatioAssumption_Gain
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 27;

                    ;% Blank_Model_P.Saturation1_UpperSat
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 28;

                    ;% Blank_Model_P.Saturation1_LowerSat
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 29;

                    ;% Blank_Model_P.Constant_Value_e
                    section.data(31).logicalSrcIdx = 30;
                    section.data(31).dtTransOffset = 30;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Blank_Model_P.Gain_Gain_h
                    section.data(1).logicalSrcIdx = 31;
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
        ;% Auto data (Blank_Model_B)
        ;%
            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Blank_Model_B.StreamInput_o1
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Blank_Model_B.StreamInput_o2
                    section.data(1).logicalSrcIdx = 1;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Blank_Model_B.StreamInput_o3
                    section.data(1).logicalSrcIdx = 2;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(3) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Blank_Model_B.StreamInput_o4
                    section.data(1).logicalSrcIdx = 3;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(4) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Blank_Model_B.StreamInput_o5
                    section.data(1).logicalSrcIdx = 4;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(5) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Blank_Model_B.StreamInput_o6
                    section.data(1).logicalSrcIdx = 5;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(6) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Blank_Model_B.StreamInput_o7
                    section.data(1).logicalSrcIdx = 6;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(7) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Blank_Model_B.StreamInput_o8
                    section.data(1).logicalSrcIdx = 7;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(8) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Blank_Model_B.StreamInput_o9
                    section.data(1).logicalSrcIdx = 8;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(9) = section;
            clear section

            section.nData     = 22;
            section.data(22)  = dumData; %prealloc

                    ;% Blank_Model_B.Gain
                    section.data(1).logicalSrcIdx = 9;
                    section.data(1).dtTransOffset = 0;

                    ;% Blank_Model_B.Gain_n
                    section.data(2).logicalSrcIdx = 10;
                    section.data(2).dtTransOffset = 1;

                    ;% Blank_Model_B.TSamp
                    section.data(3).logicalSrcIdx = 11;
                    section.data(3).dtTransOffset = 2;

                    ;% Blank_Model_B.Diff
                    section.data(4).logicalSrcIdx = 12;
                    section.data(4).dtTransOffset = 3;

                    ;% Blank_Model_B.TSamp_c
                    section.data(5).logicalSrcIdx = 13;
                    section.data(5).dtTransOffset = 4;

                    ;% Blank_Model_B.Diff_b
                    section.data(6).logicalSrcIdx = 14;
                    section.data(6).dtTransOffset = 5;

                    ;% Blank_Model_B.Gain_b
                    section.data(7).logicalSrcIdx = 15;
                    section.data(7).dtTransOffset = 6;

                    ;% Blank_Model_B.Gain_d
                    section.data(8).logicalSrcIdx = 16;
                    section.data(8).dtTransOffset = 7;

                    ;% Blank_Model_B.Gain_np
                    section.data(9).logicalSrcIdx = 17;
                    section.data(9).dtTransOffset = 8;

                    ;% Blank_Model_B.Gain_nn
                    section.data(10).logicalSrcIdx = 18;
                    section.data(10).dtTransOffset = 9;

                    ;% Blank_Model_B.Sum
                    section.data(11).logicalSrcIdx = 19;
                    section.data(11).dtTransOffset = 10;

                    ;% Blank_Model_B.Sum1
                    section.data(12).logicalSrcIdx = 20;
                    section.data(12).dtTransOffset = 11;

                    ;% Blank_Model_B.Torque_Sat
                    section.data(13).logicalSrcIdx = 21;
                    section.data(13).dtTransOffset = 12;

                    ;% Blank_Model_B.TimingParity
                    section.data(14).logicalSrcIdx = 22;
                    section.data(14).dtTransOffset = 14;

                    ;% Blank_Model_B.Gain1
                    section.data(15).logicalSrcIdx = 23;
                    section.data(15).dtTransOffset = 15;

                    ;% Blank_Model_B.Gain1_c
                    section.data(16).logicalSrcIdx = 24;
                    section.data(16).dtTransOffset = 16;

                    ;% Blank_Model_B.Gain1_l
                    section.data(17).logicalSrcIdx = 25;
                    section.data(17).dtTransOffset = 17;

                    ;% Blank_Model_B.Gain1_j
                    section.data(18).logicalSrcIdx = 26;
                    section.data(18).dtTransOffset = 18;

                    ;% Blank_Model_B.Gain_ny
                    section.data(19).logicalSrcIdx = 27;
                    section.data(19).dtTransOffset = 19;

                    ;% Blank_Model_B.Gain1_ca
                    section.data(20).logicalSrcIdx = 28;
                    section.data(20).dtTransOffset = 20;

                    ;% Blank_Model_B.Gain2
                    section.data(21).logicalSrcIdx = 29;
                    section.data(21).dtTransOffset = 21;

                    ;% Blank_Model_B.Gain3
                    section.data(22).logicalSrcIdx = 30;
                    section.data(22).dtTransOffset = 22;

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
        ;% Auto data (Blank_Model_DW)
        ;%
            section.nData     = 4;
            section.data(4)  = dumData; %prealloc

                    ;% Blank_Model_DW.UD_DSTATE
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% Blank_Model_DW.UD_DSTATE_h
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% Blank_Model_DW.DiscreteTimeIntegrator_DSTATE
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% Blank_Model_DW.DiscreteTimeIntegrator1_DSTATE
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 20;
            section.data(20)  = dumData; %prealloc

                    ;% Blank_Model_DW.Scope_PWORK.LoggedData
                    section.data(1).logicalSrcIdx = 4;
                    section.data(1).dtTransOffset = 0;

                    ;% Blank_Model_DW.Scope_PWORK_k.LoggedData
                    section.data(2).logicalSrcIdx = 5;
                    section.data(2).dtTransOffset = 1;

                    ;% Blank_Model_DW.Scope1_PWORK.LoggedData
                    section.data(3).logicalSrcIdx = 6;
                    section.data(3).dtTransOffset = 2;

                    ;% Blank_Model_DW.Scope2_PWORK.LoggedData
                    section.data(4).logicalSrcIdx = 7;
                    section.data(4).dtTransOffset = 3;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_Demux_at_outport_0_PWORK.AQHandles
                    section.data(5).logicalSrcIdx = 8;
                    section.data(5).dtTransOffset = 4;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_Demux_at_outport_1_PWORK.AQHandles
                    section.data(6).logicalSrcIdx = 9;
                    section.data(6).dtTransOffset = 5;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_Demux_at_outport_2_PWORK.AQHandles
                    section.data(7).logicalSrcIdx = 10;
                    section.data(7).dtTransOffset = 6;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_Demux_at_outport_3_PWORK.AQHandles
                    section.data(8).logicalSrcIdx = 11;
                    section.data(8).dtTransOffset = 7;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_DiscreteDerivative1_at_outport_0_PWORK.AQHandles
                    section.data(9).logicalSrcIdx = 12;
                    section.data(9).dtTransOffset = 8;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_DiscreteDerivative_at_outport_0_PWORK.AQHandles
                    section.data(10).logicalSrcIdx = 13;
                    section.data(10).dtTransOffset = 9;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_RadianstoDegrees1_at_outport_0_PWORK.AQHandles
                    section.data(11).logicalSrcIdx = 14;
                    section.data(11).dtTransOffset = 10;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_RadianstoDegrees2_at_outport_0_PWORK.AQHandles
                    section.data(12).logicalSrcIdx = 15;
                    section.data(12).dtTransOffset = 11;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_RadianstoDegrees3_at_outport_0_PWORK.AQHandles
                    section.data(13).logicalSrcIdx = 16;
                    section.data(13).dtTransOffset = 12;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_RadianstoDegrees4_at_outport_0_PWORK.AQHandles
                    section.data(14).logicalSrcIdx = 17;
                    section.data(14).dtTransOffset = 13;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_RadianstoDegrees5_at_outport_0_PWORK.AQHandles
                    section.data(15).logicalSrcIdx = 18;
                    section.data(15).dtTransOffset = 14;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_RadianstoDegrees_at_outport_0_PWORK.AQHandles
                    section.data(16).logicalSrcIdx = 19;
                    section.data(16).dtTransOffset = 15;

                    ;% Blank_Model_DW.StreamOutput_PWORK
                    section.data(17).logicalSrcIdx = 20;
                    section.data(17).dtTransOffset = 16;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_Saturation1_at_outport_0_PWORK.AQHandles
                    section.data(18).logicalSrcIdx = 21;
                    section.data(18).dtTransOffset = 18;

                    ;% Blank_Model_DW.StreamInput_PWORK
                    section.data(19).logicalSrcIdx = 22;
                    section.data(19).dtTransOffset = 19;

                    ;% Blank_Model_DW.TAQSigLogging_InsertedFor_StringtoDouble8_at_outport_0_PWORK.AQHandles
                    section.data(20).logicalSrcIdx = 23;
                    section.data(20).dtTransOffset = 21;

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


    targMap.checksum0 = 1594619151;
    targMap.checksum1 = 611761312;
    targMap.checksum2 = 3257797441;
    targMap.checksum3 = 1775289076;

