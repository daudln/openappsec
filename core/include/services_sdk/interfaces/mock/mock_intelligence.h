#ifndef __MOCK_INTELLIGENCE_H__
#define __MOCK_INTELLIGENCE_H__

#include "i_intelligence_is_v2.h"
#include "cptest.h"

std::ostream &
operator<<(std::ostream &os, const Intelligence::Response &)
{
    return os;
}

std::ostream &
operator<<(std::ostream &os, const Intelligence::Invalidation &)
{
    return os;
}

class MockIntelligence : public Singleton::Provide<I_Intelligence_IS_V2>::From<MockProvider<I_Intelligence_IS_V2>>
{
public:
    using InvalidationCb = std::function<void(const Intelligence::Invalidation &)>;
    using Invalidation = Intelligence::Invalidation;
    using Response = Intelligence::Response;

    MOCK_CONST_METHOD1(sendInvalidation, bool(const Invalidation &invalidation));
    MOCK_METHOD2(registerInvalidation, Maybe<uint>(const Invalidation &invalidation, const InvalidationCb &callback));
    MOCK_METHOD1(unregisterInvalidation, void(uint id));
    MOCK_CONST_METHOD3(
        getResponse,
        Maybe<Response>(const std::vector<QueryRequest> &query_requests, bool is_pretty, bool is_bulk)
    );
    MOCK_CONST_METHOD2(getResponse, Maybe<Response>(const QueryRequest &query_request, bool is_pretty));
    MOCK_CONST_METHOD0(getIsOfflineOnly, bool(void));
    MOCK_CONST_METHOD1(getOfflineInfoString, Maybe<std::string>(const SerializableQueryFilter &query));
};

#endif // __MOCK_INTELLIGENCE_H__
