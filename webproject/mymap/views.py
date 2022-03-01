from django.shortcuts import render
from django.http import HttpResponse

from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
import json

from  .algorithm.calGeothermal import Geothermal
import os

import pandas as pd
# from algorithm.calGeothermal import Geothermal


# Create your views here.
def index( request):
    return render(request, 'mymap/home.html')

@csrf_exempt
def calTemp( request):
	req = json.loads( request.body )
	print(req)
	geo = Geothermal( os.getcwd()+'\\mymap\\data\\')

	selPos = req['selPos']
	depth = req['depth']
	result = geo.caltmprt( float(depth) )
	return JsonResponse( {'temperature': str(round(result, 1)) })



