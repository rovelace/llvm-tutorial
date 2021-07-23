#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "DynamicCallCount.h"

bool DynamicCallCount::runOnModule(Module &M) {
	
	Type * voidTy = Type::getVoidTy(M.getContext());
	FunctionCallee cc = M.getOrInsertFunction("countCall", voidTy);
	FunctionCallee pr = M.getOrInsertFunction("printResult", voidTy);
	for (Function &F : M){
		for (BasicBlock &B : F){
			for (Instruction &I : B){
			if (auto CC = dyn_cast<CallInst> (&I)) {
				IRBuilder<> Builder(&I);
				Builder.CreateCall(cc.getFunctionType(), cc.getCallee());
			}
			if (auto CC = dyn_cast<ReturnInst> (&I)) {
				IRBuilder<> Builder(&I);
				Builder.CreateCall(pr.getFunctionType(), pr.getCallee());
			}

			}
		}
	}
    return false;
}

void DynamicCallCount::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
}

char DynamicCallCount::ID = 0;
static RegisterPass<DynamicCallCount> Y("dyn-call-count", "DynamicCallCount Pass ");

//clang test.opt.bc -L../Runtime -l :callCount.so -o test.exe
//LD_LIBRARY_PATH=../Runtime ./test.exe
