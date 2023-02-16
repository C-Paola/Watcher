package com.example.appembebidos.ui.main;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import com.example.appembebidos.R;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class ButtonFragment extends Fragment {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {

        View root = inflater.inflate(R.layout.fragment_button, container, false);

        // Write a message to the database
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        FirebaseDatabase database1 = FirebaseDatabase.getInstance();
        DatabaseReference myRef = database.getReference("led");
        DatabaseReference myRef1 = database1.getReference("led1");

        final ToggleButton mledToggleButton = root.findViewById(R.id.toggleButton);
        final ToggleButton mledToggleButton1 = root.findViewById(R.id.toggleButton1);

        mledToggleButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mledToggleButton.isChecked()){
                    myRef.setValue(1);
                }else{
                    myRef.setValue(0);
                }
            }
        });
        mledToggleButton1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mledToggleButton1.isChecked()){
                    myRef1.setValue(1);
                }else{
                    myRef1.setValue(0);
                }
            }
        });
        return root;
    }
}