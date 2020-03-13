#ifndef ResourceService_hpp
#define ResourceService_hpp

#include <unordered_map>
#include <string>

// TODO move away from resource manager for all types

template <class T>
struct Resource
{
    T* ptr;
    int count;
};

using namespace std;

template <class T>
class ResourceService
{
private:
    ResourceService<T>(){};
    
    unordered_map<string, Resource<T>> m_resourceDirectory;
    
    inline static ResourceService<T>* m_instance = NULL;
public:
    
    static ResourceService<T>* GetInstance() noexcept
    {
        if(m_instance == NULL){
            m_instance = new ResourceService<T>();
        }
        return m_instance;
    }

    T* Request(string key) noexcept
    {
        T* p_resource = NULL;    
        auto result = m_resourceDirectory.find(key);
        if (result != m_resourceDirectory.end())
        {
            p_resource = result->second.ptr;
            result->second.count++;
        }
        else
        {
            Resource<T> resource;
            resource.ptr = new T(key);
            resource.count = 0;
            m_resourceDirectory.insert({key,resource});

            p_resource = resource.ptr;
        }
        return p_resource;
    }
    
    void Dispose(string key) noexcept
    {
        auto result = m_resourceDirectory.find(key);
        if (result != m_resourceDirectory.end())
        {
            T* resource = result->second.ptr;
            
            if(--result.count <= 0)
            {
                delete resource;
                m_resourceDirectory.erase(key);
            }
        }    
    }
};



#endif // ResourceService_hpp