# -*- coding: utf-8 -*-
import scrapy
from scrapy.spider import BaseSpider
from scrapy.selector import HtmlXPathSelector
from scrapy.contrib.loader import XPathItemLoader
from scrapy.contrib.loader.processor import Join, MapCompose
from scrapy.http.request import Request
from conferences.items import PaperItem

from bs4 import BeautifulSoup

class CvprSpider(BaseSpider):
    name = "cvpr"
    allowed_domains = ["cv-foundation.org"]
    start_urls = (
        'http://www.cv-foundation.org/openaccess/CVPR2015.py',
    )
    # http://www.cv-foundation.org/openaccess/content_cvpr_2015/papers/Szegedy_Going_Deeper_With_2015_CVPR_paper.pdf
    def __init__(self):
        self.prefix = "http://www.cv-foundation.org/openaccess/"

    def parse(self, response):
        soup = BeautifulSoup(str(response.body), 'lxml')
        links = soup.find_all('a')
        file_urls = []
        item = PaperItem()
        for link in links:
            l = link.get('href')
            if not l:
                continue
            if l[-4:] != ".pdf":
                continue
            url = self.prefix + l
            file_urls.append(url)
        item['file_urls'] = file_urls
        yield item
