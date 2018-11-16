FEATURE script.h/Impl
//! Provide key-value coding scriptable API host.
class KVC
{
    public:
        KVC(Environment *environment) : environment(environment) { }

        ~KVC() { }

        void registerKey(
            const std::string &key,
            EnvironmentClient::CallbackCall callback
        ) {
            auto client = new script::EnvironmentClient;
            client->call = callback;
            this->clients.push_back(client);
            this->environment->addClient(client, {key});
        }

    private:
        Environment *environment;
        std::vector<EnvironmentClient *> clients;
};
