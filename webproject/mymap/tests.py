from django.test import TestCase

# Create your tests here.
from  algorithm.calGeothermal import Geothermal

geo = Geothermal('data/')
print(geo.caltmprt(10))
