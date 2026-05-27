import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class SensorService {

  private apiUrl = environment.apiUrl;

  constructor(private http: HttpClient) {}

  getUltimaLeitura() {
    return this.http.get(`${this.apiUrl}/dados`);
  }

  getHistorico() {
    return this.http.get<any[]>(`${this.apiUrl}/historico`);
  }
}