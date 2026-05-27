import {
  Component,
  ElementRef,
  OnDestroy,
  OnInit,
  ViewChild
} from '@angular/core';

import { ChangeDetectorRef } from '@angular/core';

import { SensorService } from '../services/sensor.service';

import {
  Chart,
  LineController,
  LineElement,
  PointElement,
  LinearScale,
  CategoryScale,
  Tooltip,
  Legend,
  Filler
} from 'chart.js';

Chart.register(
  LineController,
  LineElement,
  PointElement,
  LinearScale,
  CategoryScale,
  Tooltip,
  Legend,
  Filler
);

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
  standalone: false
})
export class HomePage implements OnInit, OnDestroy {

  @ViewChild('lineCanvas') lineCanvas!: ElementRef;

  temperatura = 0;
  umidade = 0;
  distancia = 0;

  chart: any;

  intervalo: any;

  constructor(private sensorService: SensorService, private cdr: ChangeDetectorRef) {}

  ngOnInit() {

    setTimeout(() => {
      this.createChart();
    }, 500);

    this.carregarDados();

    this.intervalo = setInterval(() => {
      this.carregarDados();
    }, 3000);
  }

  carregarDados() {

    this.sensorService.getUltimaLeitura().subscribe((dados: any) => {
      

      this.temperatura = Number(dados[0].temperatura);
      this.umidade = Number(dados[0].umidade);
      this.distancia = Number(dados[0].distancia);

    });

    this.sensorService.getHistorico().subscribe((dados: any[]) => {


      const historico = [...dados].reverse();

      const labels = historico.map((_, index) => `${index + 1}`);

      const temperaturas = historico.map(item => item.temperatura);

      if(this.chart) {

        this.chart.data.labels = labels;
        this.chart.data.datasets[0].data = temperaturas;

        this.chart.update();
      }
    });
  }

  createChart() {

    this.chart = new Chart(this.lineCanvas.nativeElement, {

      type: 'line',

      data: {

        labels: [],

        datasets: [
          {
            label: 'Temperatura',
            data: [],
            borderColor: '#00ffd5',
            backgroundColor: 'rgba(0,255,213,0.15)',
            fill: true,
            tension: 0.4,
            pointRadius: 3
          }
        ]
      },

      options: {

        responsive: true,
        maintainAspectRatio: false,

        plugins: {
          legend: {
            labels: {
              color: 'white'
            }
          }
        },

        scales: {

          x: {
            ticks: {
              color: 'white'
            },
            grid: {
              color: 'rgba(255,255,255,0.08)'
            }
          },

          y: {
            ticks: {
              color: 'white'
            },
            grid: {
              color: 'rgba(255,255,255,0.08)'
            }
          }
        }
      }
    });
  }

  ngOnDestroy() {
    clearInterval(this.intervalo);
  }
}