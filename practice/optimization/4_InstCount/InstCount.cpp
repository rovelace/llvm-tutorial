#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Instructions.h"
#include "InstCount.h"

bool InstCount::runOnFunction(Function &F) {
	int cnt = 0;
	for (auto &BB : F){
	for (auto &II : BB){
		cnt++;
	}
	}
	dbgs() << F.getName() << ":" << cnt << "\n";
    return false;
}

void InstCount::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
}

char InstCount::ID = 0;
static RegisterPass<InstCount> Y("inst-count", "InstCount Pass ");
