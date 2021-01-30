#include "router/jsfunction.h"

QJSValue newFunction(QJSEngine* forEngine, std::function<void(QJSValue)> f)
{
    auto transformer = forEngine->evaluate(R"(
(function(instance) {
    return function(...args) {
        return instance(Array.from(args))
    }
})
)");
    auto transformed = transformer.call({forEngine->newQObject(new Caller(f))});
    return transformed;
}
