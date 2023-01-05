#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"


namespace llvm {
    class FunctionNames : public PassInfoMixin<FunctionNames> {
    public:
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
    };

    // bypasses clang 'optnone' when generating IR files with `-O0` flag
    static bool isRequired() { return true; }
}

using namespace llvm;

PreservedAnalyses FunctionNames::run(Function &F, 
                                          FunctionAnalysisManager &AM) {
    errs() << F.getName() << "\n";

return PreservedAnalyses::all();
}


// New PM registration
llvm::PassPluginLibraryInfo getShallowCallCounterPluginInfo() {
return {LLVM_PLUGIN_API_VERSION, "FunctionNames", LLVM_VERSION_STRING,
    [](PassBuilder &PB) {
        PB.registerPipelineParsingCallback(
            [](StringRef Name, FunctionPassManager &FPM,
               ArrayRef<PassBuilder::PipelineElement>) {
            if (Name == "fn-name") {
                FPM.addPass(FunctionNames());
                return true;
            }
            return false;
        });
    }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return getShallowCallCounterPluginInfo();
}
