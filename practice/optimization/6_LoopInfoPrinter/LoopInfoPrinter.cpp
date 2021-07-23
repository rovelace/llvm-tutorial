#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Instructions.h"

#include "llvm/Analysis/LoopInfo.h"

#include "LoopInfoPrinter.h"

bool LoopInfoPrinter::runOnFunction(Function &F) {
	LoopInfo &LI = getAnalysis<LoopInfoWrapperPass> ().getLoopInfo();
	dbgs() << F.getName() << ":\n" ;
	
	SmallVector<Loop *, 4> loops = LI.getLoopsInPreorder();
	for (int i = 0; i <  loops.size() ; i ++) {
		auto LL = loops[i];
		auto subloops = LL->getSubLoops();
		dbgs() << LL->getName() << "- depth:" << LL->getLoopDepth() << " subloops:" << subloops.size() <<
			" numblocks:" << LL->getNumBlocks() <<
			" backedges:"<< LL->getNumBackEdges()<< "\n";
	}


    return false;
}

void LoopInfoPrinter::getAnalysisUsage(AnalysisUsage &AU) const {
	AU.addRequired<LoopInfoWrapperPass>();
    AU.setPreservesAll();
}

char LoopInfoPrinter::ID = 0;
static RegisterPass<LoopInfoPrinter> Y("loop-info-printer", "LoopInfoPrinter Pass ");
