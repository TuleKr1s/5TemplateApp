from icrawler.builtin import GoogleImageCrawler
import os

dirPath = os.path.dirname(os.path.realpath(__file__))

# jpeg jpg gif

def parser(request):
    google_crawler = GoogleImageCrawler(storage={'root_dir': f'{dirPath}/downloaded icons'})
    finalRequest = request + "icon png"

    google_crawler.crawl(keyword=finalRequest, filters=dict(size = "medium"), max_num=1)




with open(f"{dirPath}/program name.txt") as f:
    request = f.readline()

finalPath = f'{dirPath}/downloaded icons/000001.'

if os.path.exists(f'{finalPath}png'):
    os.remove(f'{finalPath}png')
elif os.path.exists(f'{finalPath}jpg'):
    os.remove(f'{finalPath}jpg')
elif os.path.exists(f'{finalPath}jpeg'):
    os.remove(f'{finalPath}jpeg')
elif os.path.exists(f'{finalPath}gif'):
    os.remove(f'{finalPath}gif')

parser(request)



if os.path.exists(f'{finalPath}png'):
    os.rename(f'{finalPath}png', f'{dirPath}/downloaded icons/{request}.png')
elif os.path.exists(f'{finalPath}jpg'):
    os.rename(f'{finalPath}jpg', f'{dirPath}/downloaded icons/{request}.png')
elif os.path.exists(f'{finalPath}jpeg'):
    os.rename(f'{finalPath}jpeg', f'{dirPath}/downloaded icons/{request}.png')
elif os.path.exists(f'{finalPath}gif'):
    os.rename(f'{finalPath}gif', f'{dirPath}/downloaded icons/{request}.png')