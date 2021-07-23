#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Instructions.h"
#include "CallCount.h"

bool CallCount::runOnFunction(Function &F) {
	int cnt = 0;
	for ( auto & BB :F){
		for (auto& II :BB){
			if (auto CC = dyn_cast<CallInst> (&II)){
				cnt++;
			}
		}
	}

	dbgs() << F.getName() << ":" <<cnt << "\n";
    return false;
}

void CallCount::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
}

char CallCount::ID = 0;
static RegisterPass<CallCount> Y("callcount", "CallCount Pass ");
