#include "RequestManager.h"

const char REPLY_KEY[] = "replyKey";

RequestManager::RequestManager(QObject *parent) : QObject(parent)
{
    _userAgentArray
            << "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36 OPR/105.0.0.0"
        << "Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36"
        << "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.183 Safari/537.36 Vivaldi/1.96.1137.3"
        << "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.102 YaBrowser/20.9.1.112 Yowser/2.5 Safari/537.36"
        << "Mozilla/5.0 (iPhone; CPU iPhone OS 14_7 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/14.0 YaBrowser/21.6.3.883.10 SA/3 Mobile/15E148 Safari/604.1"
        << "Mozilla/5.0 (X11; Fedora; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.117 Safari/537.36";
    _manager = new QNetworkAccessManager(this);
    _ruPochtaRequest = new RuPochtaRequest(this);
    _cainiaoRequest = new CainiaoRequest(this);
    _globalRequest = new GlobalCainiaoRequest(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(successReply(QNetworkReply*)));
}

RequestManager::~RequestManager()
{
    delete _manager;
}

void RequestManager::getBarcodeData(const QString barcode, const PostService postService)
{
    emit loadingStateCallback(LoadingStatus::LOADING);
    if (postService == PostService::RU_POCHTA)
    {
        QNetworkRequest request = _ruPochtaRequest->getDetails(barcode);
        request.setRawHeader("User-Agent", getUserAgent());
        QNetworkReply *reply = _manager->get(request);
        reply->setProperty(REPLY_KEY, PostService::RU_POCHTA);
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorReply(QNetworkReply::NetworkError)));
    }
    else if (postService == PostService::GLOBAL_CAINIAO)
    {
        QNetworkRequest request = _globalRequest->getDetails(barcode);
        request.setRawHeader("User-Agent", getUserAgent());
        QNetworkReply *reply = _manager->get(request);
        reply->setProperty(REPLY_KEY, PostService::GLOBAL_CAINIAO);
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorReply(QNetworkReply::NetworkError)));
    }
    else
    {
        PostData data = _cainiaoRequest->getDetails(barcode);
        QNetworkRequest request = data.getRequest();
        request.setRawHeader("User-Agent", getUserAgent());
        QNetworkReply *reply = _manager->post(request, data.getPart());
        reply->setProperty(REPLY_KEY, PostService::CAINIAO);
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorReply(QNetworkReply::NetworkError)));
    }
}

QByteArray RequestManager::getUserAgent()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, _userAgentArray.size() - 1);
    return _userAgentArray.at(distr(gen));
}

void RequestManager::successReply(QNetworkReply *reply)
{
    const QVariant type = reply->property(REPLY_KEY);
    if (type.isValid())
    {
        const PostService postService = type.value<PostService>();
        if (postService == PostService::RU_POCHTA)
        {
            PochtaItem *details = _ruPochtaRequest->parseReply(reply);
            if (details != nullptr)
            {
                emit loadingStateCallback(LoadingStatus::SUCCESS);
                emit detailsReply(ItemConverter::convertItem(details));
                details->deleteLater();
            }
            else
            {
                emit loadingStateCallback(LoadingStatus::ERROR, new CustomError(this, ErrorType::EMPTY_RESPONSE));
            }
        }
        else if (postService == PostService::GLOBAL_CAINIAO)
        {
            GlobalCainiaoItem *item = _globalRequest->parseReply(reply);
            if (item != nullptr)
            {
                emit loadingStateCallback(LoadingStatus::SUCCESS);
                emit detailsReply(ItemConverter::convertItem(item));
                item->deleteLater();
            }
            else
            {
                emit loadingStateCallback(LoadingStatus::ERROR, new CustomError(this, ErrorType::EMPTY_RESPONSE));
            }
        }
        else if (postService == PostService::CAINIAO)
        {
            CainiaoItem *item = _cainiaoRequest->parseReply(reply);
            if (item != nullptr)
            {
                emit loadingStateCallback(LoadingStatus::SUCCESS);
                emit detailsReply(ItemConverter::convertItem(item));
                item->deleteLater();
            }
            else
            {
                emit loadingStateCallback(LoadingStatus::ERROR, new CustomError(this, ErrorType::EMPTY_RESPONSE));
            }
        }
        else
        {
            emit loadingStateCallback(LoadingStatus::ERROR, new CustomError(this, ErrorType::WRONG_SERVICE));
        }
    }
    reply->deleteLater();
}

void RequestManager::errorReply(QNetworkReply::NetworkError error)
{
    qDebug() << "errorReply: " << "error: " << error;
    emit loadingStateCallback(LoadingStatus::ERROR, new CustomError());
}
