#ifndef ResourceService_hpp
#define ResourceService_hpp

#include <vector>
#include <string>
#include <gsl/pointers>
#include <memory>

template <class T>
struct Resource
{
    std::string m_key;
    time_t m_lastModified;
    std::unique_ptr<T> m_data;
    int m_count;

    void ResetIfModified();
};

template <class T>
class ResourceService
{
private:
    ResourceService<T>(){};
    std::vector<Resource<T>> m_resources;
    inline static ResourceService<T>* m_instance = NULL;
public:
    
    static ResourceService<T>* GetInstance() noexcept
    {
        if(m_instance == NULL){
            m_instance = new ResourceService<T>();
        }
        return m_instance;
    }

    T* Request(std::string key) noexcept
    {
        for(int i = 0; i < m_resources.size(); ++i)
        {
            if(m_resources[i].m_key == key)
            {
                return m_resources[i].m_data.get();
            }
        }
        Resource<T> resource;
        resource.m_key = key;

        resource.ptr = make_unique<T>(key);
        resource.count = 0;
        auto ptr = resource.ptr.get();
        m_resources.push_back({key,resource});
        return ptr;
    }
    
    void Dispose(std::string key) noexcept
    {
        for(int i = 0; i < m_resources.size(); ++i)
        {
            if(m_resources[i].m_key == key)
            {
                if(--m_resources[i].m_count <= 0)
                {
                    m_resources.erase(i);
                    return;
                }
            }
        }
    }
};

#endif // ResourceService_hpp