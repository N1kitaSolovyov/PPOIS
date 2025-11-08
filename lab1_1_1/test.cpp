#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "Tape.h"
#include "PostProgram.h" 
#include "PostMachine.h"

class TapeTest : public ::testing::Test {
protected:
    Tape tape;
};

TEST_F(TapeTest, DefaultConstructor) {
    EXPECT_FALSE(tape.read());
    EXPECT_EQ(tape.getHeadPosition(), 0);
}



TEST_F(TapeTest, MoveRight) {
    tape.moveRight();
    EXPECT_EQ(tape.getHeadPosition(), 1);
    EXPECT_FALSE(tape.read());
}

TEST_F(TapeTest, MoveLeft) {
    tape.moveLeft();
    EXPECT_EQ(tape.getHeadPosition(), -1);
    EXPECT_FALSE(tape.read());
}

TEST_F(TapeTest, LoadFromString) {
    tape.loadFromString("101");
    EXPECT_TRUE(tape.read());
}

TEST_F(TapeTest, LoadEmptyString) {
    tape.loadFromString("");
    EXPECT_EQ(tape.toString(), "[0]");
}

TEST_F(TapeTest, CopyConstructor) {
    tape.loadFromString("101");
    Tape copy(tape);
    EXPECT_EQ(tape.toString(), copy.toString());
    EXPECT_EQ(tape.getHeadPosition(), copy.getHeadPosition());
}

TEST_F(TapeTest, AssignmentOperator) {
    tape.loadFromString("101");
    Tape another;
    another = tape;
    EXPECT_EQ(tape.toString(), another.toString());
}


class PostProgramTest : public ::testing::Test {
protected:
    PostProgram program;
};

TEST_F(PostProgramTest, AddCommand) {
    program.addCommand(1, 'R', 2);
    EXPECT_TRUE(program.hasCommand(1));
}

TEST_F(PostProgramTest, RemoveCommand) {
    program.addCommand(1, 'R', 2);
    program.removeCommand(1);
    EXPECT_FALSE(program.hasCommand(1));
}

TEST_F(PostProgramTest, GetCommandType) {
    program.addCommand(1, 'V', 2);
    EXPECT_EQ(program.getCommandType(1), 'V');
}

TEST_F(PostProgramTest, GetNextCommandMovement) {
    program.addCommand(1, 'R', 2);
    EXPECT_EQ(program.getNextCommand(1, false), 2);
}

TEST_F(PostProgramTest, GetNextCommandConditionTrue) {
    program.addCommand(1, '?', 2, 3);
    EXPECT_EQ(program.getNextCommand(1, true), 2);
}

TEST_F(PostProgramTest, GetNextCommandConditionFalse) {
    program.addCommand(1, '?', 2, 3);
    EXPECT_EQ(program.getNextCommand(1, false), 3);
}

TEST_F(PostProgramTest, LoadFromStream) {
    std::stringstream ss("1: R 2\n2: !\n");
    program.loadFromStream(ss);
    EXPECT_TRUE(program.hasCommand(1));
    EXPECT_TRUE(program.hasCommand(2));
}


class PostMachineTest : public ::testing::Test {
protected:
    PostMachine machine;
};

TEST_F(PostMachineTest, LoadProgramFromStream) {
    std::stringstream ss("1: R 2\n2: !\n");
    machine.loadProgramFromStream(ss);
    EXPECT_TRUE(machine.hasCommand(1));
}

TEST_F(PostMachineTest, LoadTapeFromString) {
    machine.loadTapeFromString("101");
    std::string tapeStr = machine.getTapeString();
    EXPECT_NE(tapeStr.find("1"), std::string::npos);
}

TEST_F(PostMachineTest, StepMovementRight) {
    machine.addCommand(1, 'R', 2);
    machine.addCommand(2, '!');
    machine.loadTapeFromString("1");

    bool canContinue = machine.step();
    EXPECT_TRUE(canContinue);
    EXPECT_FALSE(machine.isHalted());
}

TEST_F(PostMachineTest, StepMovementLeft) {
    machine.addCommand(1, 'L', 2);
    machine.addCommand(2, '!');
    machine.loadTapeFromString("1");

    machine.step();
    EXPECT_EQ(machine.getCurrentCommand(), 2);
}

TEST_F(PostMachineTest, StepWrite) {
    machine.addCommand(1, 'V', 2);
    machine.addCommand(2, '!');
    machine.loadTapeFromString("0");

    machine.step();
    EXPECT_FALSE(machine.isHalted());
}

TEST_F(PostMachineTest, StepConditionTrue) {
    machine.addCommand(1, '?', 2, 3);
    machine.addCommand(2, '!');
    machine.addCommand(3, '!');
    machine.loadTapeFromString("1");

    machine.step();
    EXPECT_EQ(machine.getCurrentCommand(), 2);
}

TEST_F(PostMachineTest, StepConditionFalse) {
    machine.addCommand(1, '?', 2, 3);
    machine.addCommand(2, '!');
    machine.addCommand(3, '!');
    machine.loadTapeFromString("0");

    machine.step();
    EXPECT_EQ(machine.getCurrentCommand(), 3);
}

TEST_F(PostMachineTest, StepStop) {
    machine.addCommand(1, '!');
    machine.loadTapeFromString("1");

    bool canContinue = machine.step();
    EXPECT_FALSE(canContinue);
    EXPECT_TRUE(machine.isHalted());
}

TEST_F(PostMachineTest, RunProgram) {
    machine.addCommand(1, 'R', 2);
    machine.addCommand(2, '!');
    machine.loadTapeFromString("1");

    machine.run();
    EXPECT_TRUE(machine.isHalted());
}


TEST_F(PostMachineTest, AddRemoveCommand) {
    machine.addCommand(1, 'R', 2);
    EXPECT_TRUE(machine.hasCommand(1));

    machine.removeCommand(1);
    EXPECT_FALSE(machine.hasCommand(1));
}


TEST(IntegrationTest, CompleteProgramExecution) {
    PostMachine machine;
    machine.setLogging(false);

    machine.addCommand(1, 'R', 2);
    machine.addCommand(2, '!');
    machine.loadTapeFromString("111");

    machine.run();

    EXPECT_TRUE(machine.isHalted());
}

TEST(IntegrationTest, ProgramWithCondition) {
    PostMachine machine;
    machine.setLogging(false);

    machine.addCommand(1, '?', 2, 3);
    machine.addCommand(2, 'X', 4);
    machine.addCommand(3, 'V', 4);
    machine.addCommand(4, '!');

    machine.loadTapeFromString("1");

    machine.run();

    EXPECT_TRUE(machine.isHalted());
}

TEST_F(PostMachineTest, ComplexConditionalProgram) {
    machine.addCommand(1, '?', 2, 3);   
    machine.addCommand(2, 'X', 4);       
    machine.addCommand(3, 'V', 4);      
    machine.addCommand(4, '?', 5, 6);  
    machine.addCommand(5, 'R', 7);
    machine.addCommand(6, 'L', 7);
    machine.addCommand(7, '!');         

    machine.loadTapeFromString("1");     

    machine.run();

    
    EXPECT_TRUE(machine.isHalted());
}

TEST_F(PostMachineTest, InfiniteLoopDetection) {
    machine.addCommand(1, 'R', 2);
    machine.addCommand(2, 'L', 1); 

    machine.loadTapeFromString("1");
    for (int i = 0; i < 10; i++) {
        bool canContinue = machine.step();
        EXPECT_TRUE(canContinue);
        if (machine.isHalted()) break;
    }
    EXPECT_FALSE(machine.isHalted());
    EXPECT_GE(machine.getTapeString().length(), 5);
}

TEST_F(PostMachineTest, TapeExpansionBothDirections) {
    machine.addCommand(1, 'L', 2); 
    machine.addCommand(2, 'L', 3);
    machine.addCommand(3, 'L', 4);
    machine.addCommand(4, 'L', 5);
    machine.addCommand(5, 'L', 6);
    machine.addCommand(6, 'R', 7);
    machine.addCommand(7, 'R', 8);
    machine.addCommand(8, 'R', 9);
    machine.addCommand(9, 'R', 10);
    machine.addCommand(10, 'R', 11);
    machine.addCommand(11, 'R', 12);
    machine.addCommand(12, 'R', 13);
    machine.addCommand(13, 'R', 14);
    machine.addCommand(14, 'R', 15);
    machine.addCommand(15, '!');

    machine.loadTapeFromString("1");

    machine.run();

    EXPECT_TRUE(machine.isHalted());
    std::string tape = machine.getTapeString();
    EXPECT_GT(tape.length(), 10);
}

TEST_F(PostMachineTest, ComplexTapeManipulation) {
    machine.addCommand(1, 'V', 2);   
    machine.addCommand(2, 'R', 3); 
    machine.addCommand(3, 'X', 4);   
    machine.addCommand(4, 'R', 5);  
    machine.addCommand(5, 'V', 6); 
    machine.addCommand(6, 'R', 7);   
    machine.addCommand(7, 'X', 8); 
    machine.addCommand(8, 'R', 9);   
    machine.addCommand(9, 'V', 10); 
    machine.addCommand(10, 'R', 11); 
    machine.addCommand(11, 'X', 12); 
    machine.addCommand(12, 'L', 13); 
    machine.addCommand(13, 'L', 14);
    machine.addCommand(14, 'L', 15);
    machine.addCommand(15, 'L', 16);
    machine.addCommand(16, 'L', 17);
    machine.addCommand(17, '?', 18, 19); 
    machine.addCommand(18, '!');     
    machine.addCommand(19, 'V', 1); 

    machine.loadTapeFromString("000000");

    for (int i = 0; i < 50; i++) {
        if (!machine.step()) break;
    }

    std::string tape = machine.getTapeString();
  
    std::string cleanTape;
    for (char c : tape) {
        if (c != '[' && c != ']' && c != ' ') {
            cleanTape += c;
        }
    }

   
    EXPECT_FALSE(cleanTape.empty());
    
    EXPECT_LT(std::abs(machine.getCurrentCommand()), 100);
}