CC=g++
CFLAGS=-g
LDFLAGS=

default:
	$(CC) ./FuzzerStrategies/StepNValidateFuzzStrategy.cpp ./Streams/SSHClientIOStream.cpp ./MessageBuffers/BPPMessageBuffer.cpp ./MessageBuffers/MessageBuffer.cpp ./InputGenerators/ValidInvalidInputGenerator.cpp ./InputGenerators/PacketGenerators/SSHKexInitPGen.cpp ./InputGenerators/PacketGenerators/SSHNewKeysPGen.cpp ./InputGenerators/PacketGenerators/SSHKexDHInitPGen.cpp ./InputGenerators/PacketGenerators/SSHVersionPGen.cpp ./InputGenerators/PacketGenerators/PacketGenerator.cpp ./main.cpp ./Fuzzers/SSHHandshakeStepNValidateFuzzer.cpp $(CLAGS) $(LDFLAGS) -o fuzzer

clean:
	rm fuzzer
