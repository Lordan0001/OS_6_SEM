#pragma once
#include <fstream>

extern std::fstream LogCOM;
extern long Seq;
#define SEQ LONG __XXCSeq=InterlockedIncrement(&Seq)
#define LOG(x,y) LogCOM<<__XXCSeq<<":"<<(x)<<(y)<<std::endl

extern std::fstream LogHT;
extern long SeqHT;
#define SEQHT LONG __XXCSeqHT=SeqHT

#define LOGHT(x,y) {\
	std::ofstream fout("D:\\lab7\\ofstream.txt",std::ios::app);\
	fout << InterlockedIncrement(&SeqHT) << ":" << (x) << (y) << std::endl;\
	fout.close();\
}